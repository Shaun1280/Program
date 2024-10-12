from typing import Optional, List
from joblib import Parallel, delayed
import random
from tqdm import tqdm
import logging
import os
import numpy as np

if os.path.exists("log.txt"):
    os.remove("log.txt")

def setup_logger():
    logger = logging.getLogger(__name__)
    logger.setLevel(level = logging.INFO)
    handler = logging.FileHandler("log.txt")
    handler.setLevel(logging.INFO)
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - in line: %(lineno)d %(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    return logger

# Initialize the global logger
logger = setup_logger()

# params may include (idx, ...)
def f(x: int) -> Optional[int]:
    MAX_RETRY = 2
    retry = 0

    while retry <= MAX_RETRY:
        try:
            if not logger.handlers:
                setup_logger()

            if np.random.default_rng().random() < 0.10:
                raise ValueError("Error in f({})".format(x))

            return x, x * x
        except Exception as e:
            retry += 1
            if retry <= MAX_RETRY:
                e = "{}, {}, retrying no.{}".format(x, e, retry)
                logger.error(e)
            else:
                e = "{}, {}, failed after {} retries".format(x, e, retry - 1)
                logger.error(e)
    
    return x, None

if __name__ == '__main__':
    N_JOBS = 8

    try:
        RETRIES = 5
        
        failed_jobs = []
        results = Parallel(n_jobs=N_JOBS)(
            delayed(f)(i) for i in tqdm(range(100000), desc="Processing")
        )

        for _ in range(RETRIES):
            failed_jobs_args: List[tuple] = [result[0 : -1] for result in results if result[-1] is None]
            logger.info(failed_jobs_args)

            if len(failed_jobs_args):
                rerun_results = Parallel(n_jobs=N_JOBS)(
                    delayed(f)(*args) for args in tqdm(failed_jobs_args, desc="Rerunning failed jobs")
                )
                for rerun_result in rerun_results:
                    results[rerun_result[0]] = rerun_result
            else:
                break
        
        if len(failed_jobs):
            logger.error("Jobs still fail after {} retries".format(RETRIES))
            logger.error(failed_jobs)
        else:
            logger.info("Successfully run all jobs")

        for i in range(len(results)):
            if results[i][-1] != i * i:
                logger.warning(results[i])
    except Exception as e:
        e = "{}, {}".format(__file__, e)
        logger.info(e)

    print("ok")
