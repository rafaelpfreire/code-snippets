#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace boost::asio;

int main()
{
  io_context iocontext;

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
