#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <ctime>
#include <array>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

io_context iocontext;

// Client
tcp::resolver resolv{iocontext};
tcp::socket client_tcp_socket{iocontext};
std::array<char, 4096> bytes;

// Server
tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp::acceptor tcp_acceptor{iocontext, tcp_endpoint};
tcp::socket server_tcp_socket{iocontext};
std::string data;

void client_read_handler(const boost::system::error_code &ec,
    std::size_t bytes_transferred)
{
    if (!ec)
    {
        std::cout.write(bytes.data(), bytes_transferred);
        client_tcp_socket.async_read_some(buffer(bytes), client_read_handler);
    }
}

void client_connect_handler(const boost::system::error_code &ec)
{
    if (!ec)
    {
        write(client_tcp_socket, buffer(""));
        client_tcp_socket.async_read_some(buffer(bytes), client_read_handler);
    }
}

void client_resolve_handler(const boost::system::error_code &ec,
    tcp::resolver::iterator it)
{
  if (!ec)
    client_tcp_socket.async_connect(*it, client_connect_handler);
}

void server_write_handler(const boost::system::error_code &ec,
    std::size_t bytes_transferred)
{
    if (!ec)
        server_tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void server_accept_handler(const boost::system::error_code &ec)
{
    if (!ec)
    {
        std::time_t now = std::time(nullptr);
        data = std::ctime(&now);
        async_write(server_tcp_socket, buffer(data), server_write_handler);
    }
}

int main()
{
    tcp_acceptor.listen();
    tcp_acceptor.async_accept(server_tcp_socket, server_accept_handler);

    tcp::resolver::query q{"localhost", "2014"};
    resolv.async_resolve(q, client_resolve_handler);

    iocontext.run();
}
