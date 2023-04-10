#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

constexpr auto N_THREADS = 3;
constexpr auto N_TIMERS = 6;

using namespace boost::asio;

int main()
{
    io_context iocontext;
    boost::asio::thread_pool pool(N_THREADS);

    // Do this if you don't want io_context::run()
    // to return after work was done
    // auto work_guard = make_work_guard(iocontext);

    iocontext.post([]() {
            std::cout << "This is a test " <<
                std::this_thread::get_id() <<
                std::endl;
            });

    for(int i = 0; i < N_TIMERS; i++) {
        steady_timer timer{iocontext, std::chrono::seconds{3}};
        timer.async_wait([](const boost::system::error_code &ec)
          { std::cout << "3 sec " <<
                std::this_thread::get_id() <<
                std::endl;
          });
    }

    for(int i = 0; i < N_THREADS; i++) {
        post(pool, boost::bind(&io_context::run, &iocontext));
    }

    pool.join();

    return 0;
}
