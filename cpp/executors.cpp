#include <iostream>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>

constexpr auto N_THREADS = 5;
constexpr auto N_TIMERS = 10;

int main() {
    std::vector<std::shared_future<void>> results;
    boost::asio::thread_pool pool(N_THREADS);
    auto executor = pool.get_executor();

    // - Dispatch: Run the function object immediately if possible. Most eager operation.
    //         Might run before dispatch returns. If inside pool, run immediately.
    //         If outside pool, add to queue.
    //
    // - Post: Submit the function for later execution. Never immediately in the same thread.
    //         Always adds to pool queue. Never blocking.
    //
    // - Defer: Submit the function for later execution. Least eager.
    //         Implies relationship between calling thread and function.
    //         Used when function is a continuation to the calling function.
    //         The function is added to the queue after the current function
    //         ends. If inside pool, adds to a thread local queue. If outside
    //         pool, add to queue. Thread posting might immediately run it.
    //         Potentially blocking.

    // Run timers in thread pool
    for(int i = 0; i < N_TIMERS; i++) {
        results.push_back(
            boost::asio::post(executor, boost::asio::use_future([i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(i * 10));
                std::cout <<
                    "Timer " << i << " " <<
                    "returning from thread " <<
                    std::this_thread::get_id() <<
                    std::endl; 
            }
        )));
    }

    // A strand is an executor and an executor adapter.
    // Its rule is: Run function objects according to the underlying
    // executor’s rules, but also run them in FIFO order and not
    // concurrently.

    // In this case, a total of 5*N_THREADS tasks will run sequentially in one single
    // thread of the thread pool
    boost::asio::strand<boost::asio::thread_pool::executor_type> strand(executor);
    for(int i = 0; i < 5*N_THREADS; i++) {
        results.push_back(
            boost::asio::post(strand, boost::asio::use_future([i]() {
                std::cout <<
                    "Task number " << i << " " <<
                    "executing in thread " <<
                    std::this_thread::get_id() <<
                    std::endl;
            }
        )));
    }

    // Wait for all tasks to finish
    for(auto result: results) {
        result.get();
    }

    return 0;
}
