#include <pthread.h>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <cerrno>
#include <chrono>
#include <cstring>
#include <iostream>
#include <string_view>
#include <thread>

static bool setAffinityForPthread( pthread_t thread, int core_id ) noexcept
{
    cpu_set_t cpuset;
    CPU_ZERO( &cpuset );
    CPU_SET( core_id, &cpuset );

    int ret = pthread_setaffinity_np( thread, sizeof( cpuset ), &cpuset );
    if ( ret != 0 )
    {
        std::cerr << "pthread_setaffinity_np failed " << std::strerror( ret ) << std::endl;
        return false;
    }

    return true;
}

static void printThreadInfo( std::string_view tag )
{
    pid_t tid = static_cast<pid_t>( syscall( SYS_gettid ) );
    int cpu = sched_getcpu();
    std::cout << " tag " << " tid=" << tid << " cpu=" << cpu << std::endl;
}

// Example A: thread sets its own affinity
void worker_self_affinity( int core_id )
{
    std::cout << "worker_self_affinity start\n";
    printThreadInfo( "before-set (self)" );
    // set own affinity via pthread_self()
    if ( core_id >= 0 )
    {
        if ( !setAffinityForPthread( pthread_self(), core_id ) )
        {
            std::cerr << "Failed to set own affinity\n";
        }
    }
    // allow scheduler to move the thread and then sample CPU
    using namespace std::chrono_literals;
    std::this_thread::sleep_for( 100ms );
    printThreadInfo( "after-set (self)" );
}

// Example B: main modifies another thread's affinity
void worker_no_affinity()
{
    std::cout << "worker_no_affinity start\n";
    for ( int i = 0; i < 5; ++i )
    {
        printThreadInfo( "worker_no_affinity running" );
        using namespace std::chrono_literals;
        std::this_thread::sleep_for( 200ms );
    }
}

int main()
{
    {
        auto ta = std::thread( worker_self_affinity, 1 );
        ta.join();
    }

    {
        using namespace std::chrono_literals;
        auto tb = std::thread( worker_no_affinity );
        std::this_thread::sleep_for( 100ms );

        if ( !setAffinityForPthread( tb.native_handle(), 1 ) )
        {
            std::cerr << "Failed to set affinity for worker thread from main\n";
        }
        else
        {
            std::cout << "Successfully set affinity for worker thread from main to core 1\n";
        }

        tb.join();
    }

    return 0;
}
