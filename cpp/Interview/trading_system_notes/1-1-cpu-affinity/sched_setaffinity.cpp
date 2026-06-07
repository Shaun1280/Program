#include <sched.h>       // cpu_set_t, CPU_ZERO, CPU_SET, sched_setaffinity
#include <sys/syscall.h> // SYS_gettid
#include <sys/types.h>   // pit_t
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

namespace CommonSched
{

inline bool setCurrentThreadCoreSched( int core_id ) noexcept
{
    cpu_set_t cpuset;
    CPU_ZERO( &cpuset );
    CPU_SET( core_id, &cpuset );

    auto tid = static_cast<pid_t>( syscall( SYS_gettid ) ); // kernel thread id (LWP)
    if ( sched_setaffinity( tid, sizeof( cpuset ), &cpuset ) == -1 )
    {
        perror( "sched_setaffinity(tid)" );
        return false;
    }

    return true;
}

inline bool setProcessCoreSched( int core_id ) noexcept
{
    cpu_set_t cpuset;
    CPU_ZERO( &cpuset );
    CPU_SET( core_id, &cpuset );

    // pid == 0 means the calling process, and the kernel will apply the affinity mask to all threads in the process.
    if ( sched_setaffinity( 0, sizeof( cpuset ), &cpuset ) == -1 )
    {
        perror( "sched_setaffinity(pid)" );
        return false;
    }

    return true;
}

inline int getCurrentThreadCoreSched() noexcept
{
    cpu_set_t cpuset;

    if ( sched_getaffinity( 0, sizeof( cpuset ), &cpuset ) == 0 )
    {
        for ( int i = 0; i < CPU_SETSIZE; ++i )
        {
            if ( CPU_ISSET( i, &cpuset ) )
            {
                return i;
            }
        }
    }
    return -1;
}

template <typename Func, typename... Args>
std::thread createThreadWithCoreSched( int core_id, std::string_view name, Func&& func, Args&&... args )
{
    return std::thread(
        [core_id = core_id, name = name, func = std::forward<Func>( func ), ... args = std::forward<Args>( args )]() mutable
        {
            if ( core_id >= 0 && !setCurrentThreadCoreSched( core_id ) )
            {
                std::cerr << "Failed to set core affinity for " << name << " (tid=" << syscall( SYS_gettid ) << ") to "
                          << core_id << std::endl;
                throw std::runtime_error( "Failed to set core affinity" );
            }

            if ( core_id >= 0 )
            {
                std::cerr << "Set core affinity for " << name << " (tid=" << syscall( SYS_gettid ) << ") to " << core_id
                          << std::endl;
            }

            std::forward<Func>( func )( std::forward<Args>( args )... );
        } );
}
} // namespace CommonSched

int main()
{
    CommonSched::setProcessCoreSched( 0 ); // Set the main thread to run on core 0

    auto worker = CommonSched::createThreadWithCoreSched( 0, "WorkerThread",
                                                          []
                                                          {
                                                              for ( int i = 0; i < 5; ++i )
                                                              {
                                                                  using namespace std::chrono_literals;
                                                                  std::cerr << "Worker thread running on core "
                                                                            << CommonSched::getCurrentThreadCoreSched()
                                                                            << ", iteration " << i << std::endl;
                                                                  std::this_thread::sleep_for( 1s );
                                                              }
                                                          } );
    worker.join();
    return 0;
}
