#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace boost::asio;

int main()
{
  io_context iocontext;

  // Do this if you don't want io_context::run()
  // to return after work was done
  //auto work_guard = make_work_guard(iocontext);

  iocontext.post([]() {
          std::cout << "This is a test" << std::endl;
          });

  steady_timer timer1{iocontext, std::chrono::seconds{3}};
  timer1.async_wait([](const boost::system::error_code &ec)
    { std::cout << "3 sec\n"; });

  steady_timer timer2{iocontext, std::chrono::seconds{3}};
  timer2.async_wait([](const boost::system::error_code &ec)
    { std::cout << "3 sec\n"; });

  // This will return only when timer1 and timer2 are done
  iocontext.run();

  return 0;
}
