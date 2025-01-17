'''
This is experimental code for shared cache using shared memory.
It's not recommended to use this in production code.
Current read write speed is 1 / 10 of local lru_cache.
It's better to implement this in C++.
'''

import struct
from typing import Callable, Union, Tuple, Any, Optional
import functools
import os
import pickle
from multiprocessing import Manager, shared_memory
from abc import ABC, abstractmethod

DEFAULT_CAPACITY = 2096 * 1024 * 1024  # 4GB
FALL_BACK_SIZE = 128

class SharedCache(ABC):
    @abstractmethod
    def put(self, key, data) -> bool:
        pass

    @abstractmethod
    def get(self, key) -> Optional[Any]:
        pass


class CyclicCache(SharedCache):
    def __init__(self, size_bytes: int, name: str):
        self.size = size_bytes
        self.name = name

        try:
            self.shm = shared_memory.SharedMemory(name=name)
            self.creator = 0
        except FileNotFoundError:
            self.shm = shared_memory.SharedMemory(
                name=name, create=True, size=size_bytes
            )
            self.creator = os.getpid()
            # Initialize header: write_pos(8) + read_pos(8) + entry_count(8)
            self.shm.buf[:24] = struct.pack("QQQ", 24, 24, 0)  # 24 is header size

        manager = Manager()
        self.lock = manager.Lock()
        self.key_dict = manager.dict()

        self.HEADER_SIZE = 24  # write_pos(8) + read_pos(8) + entry_count(8)

    def _read_bytes(self, start: int, length: int) -> bytes:
        """Read bytes handling wraparound"""
        if start + length <= self.size:
            return bytes(self.shm.buf[start : start + length])

        # Handle wraparound
        first_part = bytes(self.shm.buf[start : self.size])
        remaining = length - (self.size - start)
        second_part = bytes(
            self.shm.buf[self.HEADER_SIZE : self.HEADER_SIZE + remaining]
        )
        return first_part + second_part

    def _write_bytes(self, start: int, data: bytes) -> int:
        """Write bytes handling wraparound. Returns next write position"""
        length = len(data)
        if start + length <= self.size:
            self.shm.buf[start : start + length] = data
            return start + length

        # Handle wraparound
        first_part_size = self.size - start
        self.shm.buf[start : self.size] = data[:first_part_size]
        remaining = length - first_part_size
        self.shm.buf[self.HEADER_SIZE : self.HEADER_SIZE + remaining] = data[
            first_part_size:
        ]
        return self.HEADER_SIZE + remaining

    def _pack_entry(self, key, data) -> bytes:
        key = pickle.dumps(key, protocol=pickle.HIGHEST_PROTOCOL)
        key_length = len(key)
        data = pickle.dumps(data, protocol=pickle.HIGHEST_PROTOCOL)

        # Format: total_length(8) + key_length(8) + key + data
        total_length = 8 + 8 + len(key) + len(data)

        entry = struct.pack("QQ", total_length, key_length) + key + data
        return entry

    def _read_entry_at(self, pos: int, contain_data: bool = True) -> Union[Tuple[int, Any, Any], Tuple[int, Any]]:
        # Read length first
        length_bytes = self._read_bytes(pos, 8)
        length = struct.unpack("Q", length_bytes)[0]

        # Read key length
        key_length_byes = self._read_bytes(pos + 8, 8)
        key_length = struct.unpack("Q", key_length_byes)[0]

        # Read key
        key_bytes = self._read_bytes(pos + 16, key_length)
        key = pickle.loads(key_bytes)

        # Avoid reading all data if not needed
        if not contain_data:
            return length, key

        # Read data
        data_bytes = self._read_bytes(pos + 16 + key_length, length - 16 - key_length)
        data = pickle.loads(data_bytes)

        return length, key, data

    def _try_to_evict_locked(
        self, write_pos: int, read_pos: int, entry_count: int, entry: bytes
    ) -> Tuple[int, int]:
        while entry_count > 0:
            if read_pos <= write_pos:
                if write_pos + len(entry) <= self.size:
                    break
                elif write_pos + len(entry) - self.size + self.HEADER_SIZE <= read_pos:
                    break
            elif write_pos + len(entry) <= read_pos:
                break

            # Evict one entry
            length, evicted_key = self._read_entry_at(pos=read_pos, contain_data=False)
            del self.key_dict[evicted_key]

            # Update read_pos
            read_pos += length
            if read_pos >= self.size:
                read_pos = read_pos - self.size + self.HEADER_SIZE
            entry_count -= 1

        return read_pos, entry_count

    def put(self, key, data) -> bool:
        entry = self._pack_entry(key, data)

        with self.lock:
            write_pos, read_pos, entry_count = struct.unpack("QQQ", self.shm.buf[:24])

            # Check if entry fits
            if len(entry) > self.size - self.HEADER_SIZE:
                return False

            # entry fits, but need to check if we need to evict old entries
            read_pos, entry_count = self._try_to_evict_locked(
                write_pos, read_pos, entry_count, entry
            )

            # Write data, and calculate new write position
            self.key_dict[key] = write_pos
            new_write_pos = self._write_bytes(write_pos, entry)
            
            # Update header
            self.shm.buf[:24] = struct.pack(
                "QQQ", new_write_pos, read_pos, entry_count + 1
            )

            return True

    def get(self, key) -> Optional[Any]:
        with self.lock:
            if key not in self.key_dict:
                return None
            
            pos = self.key_dict[key]
            _, _, data = self._read_entry_at(pos)

        return data

    def __del__(self):
        print("Destructor called")
        self.shm.close()
        if self.creator == os.getpid():
            print("Unlinking shared memory")
            self.shm.unlink()


def create_shared_cache(
    capacity: int = DEFAULT_CAPACITY, name="shared_cache"
) -> SharedCache:
    """
    Create a shared cache (default 4G).
    This should be called in the main process before creating any worker processes.
    If not, worker process will not be able to access the shared cache.
    Instead, it will use its own local lru cache.
    """

    try:
        return CyclicCache(capacity, name)
    except Exception:
        return None


def shared_lru_cache(fallback_maxsize: int = FALL_BACK_SIZE):
    """
    This is a decorator that can be used to cache the result of a function call in a shared LRU cache.
    Function must be a method of a class that has a shared_cache attribute.\n 
    params:
        fallback_maxsize: the size of the lru_cache used as a fallback, can't be too large since it's
    """

    def decorator(func: Callable):
        # Use functools.lru_cache as a fallback
        @functools.lru_cache(maxsize=fallback_maxsize)
        def fallback_wrapper(self, *args, **kwargs):
            return func(self, *args, **kwargs)
        
        @functools.wraps(func)  
        def wrapper(self, *args, **kwargs):
            try:
                if self.shared_cache is None:
                    raise Exception("Failed to get shared_cache.")

                result = self.shared_cache.get((args, frozenset(kwargs.items())))
                if result is None:
                    result = func(self, *args, **kwargs)

                    if not self.shared_cache.put(
                        (args, frozenset(kwargs.items())), result
                    ):
                        raise Exception(
                            "Failed to put in shared_cache. Because of size limit."
                        )

                   #  print(f"pid = {os.getpid()} cache missed and put in shared_cache, key = {args}")
                else:
                    pass
                    # print(f"pid = {os.getpid()} used shared_cache, key = {args}")
                return result

            except Exception as e:
                # print(f"pid = {os.getpid()} Failed to get shared_cache : {e}, run the function using default lru_cache. ")

                # if failed to get shared_cache, run the function directly
                return fallback_wrapper(self, *args, **kwargs)

        return wrapper

    return decorator

'''
Usage:
from cache_utils import shared_lru_cache, create_shared_cache
import numpy as np
import multiprocessing
import time
from typing import Optional
import cProfile

class NDayOneStockLoader:
    def __init__(self, shared_cache):
        self.shared_cache = shared_cache

    def read_csv(self, path: str):
        @shared_lru_cache()
        def _read_csv(self, path: str):
            try:
                return path.encode() * 64 * 1024
            except Exception as e:
                # print(f"Error: {str(e)}")
                return None
        return _read_csv(self, path)

    def read_parquet(self, path: str):
        @shared_lru_cache()
        def _read_parquet(self, path: str):
            try:
                return path.encode() * 64 * 1024
            except Exception as e:
                # print(f"Error: {str(e)}")
                return None
        return _read_parquet(self, path)

    def load(self):
        rnd = int(np.random.default_rng().uniform(1, high=5010))
        return f"parquet/{rnd}", self.read_parquet(f"parquet/{rnd}")
        
def run_process(shared_cache):
    loader = NDayOneStockLoader(shared_cache)

    # profiler = cProfile.Profile()
    # profiler.enable()
    total = 10000
    start_time = time.time()
    for _ in range(total):
        loader.load()
        # time.sleep(np.random.default_rng().random() * 2)
    endTime = time.time()
    print(f"Process speed: {total / (endTime - start_time)}")

    # profiler.disable()
    # profiler.print_stats(sort='cumtime')

if __name__ == "__main__":
    shared_cache = create_shared_cache()

    # run_process(manager)

    num_processes = 10
    processes = [multiprocessing.Process(target=run_process, args=(shared_cache,)) for _ in range(num_processes)]
    
    for p in processes:
        p.start()

    for p in processes:
        p.join()

'''
