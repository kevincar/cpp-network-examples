#include <ctime>
#include <experimental/net>
#include <iostream>

using std::experimental::net::ip::tcp;
using std::experimental::net::ip::udp;

std::string make_daytime_string() {
  using namespace std;
  time_t now = time(NULL);
  return ctime(&now);
}

class udp_server {
public:
  udp_server(std::experimental::net::io_context* io_context)
    : socket_(*io_context, udp::endpoint(udp::v4(), 13)) {
        start_receive();
    }

private:
  void start_receive() {

    auto bound_handler = std::bind(
        &udp_server::handle_receive,
        this,
        std::placeholders::_1,
        std::placeholders::_2
        );

    this->socket_.async_receive_from(
        std::experimental::net::buffer(this->recv_buffer_),
        this->remote_endpoint_,
        bound_handler
        );
  }

  void handle_receive(std::error_code const& error, std::size_t len) {
    if(!error) {
      std::shared_ptr<std::string> message(new
          std::string(make_daytime_string()));

      auto bound_handler = std::bind( &udp_server::handle_send, this, message,
          std::placeholders::_1, std::placeholders::_2);
      this->socket_.async_send_to(std::experimental::net::buffer(*message),
          this->remote_endpoint_, bound_handler);
      this->start_receive();
    }
  }

  void handle_send(std::shared_ptr<std::string> message, std::error_code const&
      error, std::size_t len) {

  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  std::array<char, 1> recv_buffer_;
};

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
  typedef std::shared_ptr<tcp_connection> pointer;

  static pointer create(tcp::socket& socket) {
    return pointer(new tcp_connection(socket));
  }

  tcp::socket& socket() {
    return this->socket_;
  }

  void start() {
    this->message_ = make_daytime_string();

    std::experimental::net::async_write(
        this->socket_,
        std::experimental::net::buffer(this->message_),
        std::bind(&tcp_connection::handle_write, this->shared_from_this(),
          std::placeholders::_1, std::placeholders::_2)
        );
  }

private:
  tcp_connection(tcp::socket& socket) : socket_(socket) {} 

  void handle_write(std::error_code const& error, size_t bytes_transfered) {}

  tcp::socket& socket_;
  std::string message_;
};

class tcp_server {
public:
  tcp_server(std::experimental::net::io_context* io_context)
    : io_context_(io_context),
      acceptor_(*io_context, tcp::endpoint(tcp::v4(), 13)) {
        start_accept();
    }

private:
  void start_accept() {

    auto bound_handler = std::bind(
        &tcp_server::handle_accept,
        this,
        std::placeholders::_1,
        std::placeholders::_2
        );

    this->acceptor_.async_accept(
        bound_handler
        );
  }

  void handle_accept(std::error_code const& error, tcp::socket peer) {
    if(!error) {
      tcp_connection::pointer new_connection = tcp_connection::create(peer);
      new_connection->start();
    }

    start_accept();
  }

  std::experimental::net::io_context* io_context_;
  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
  try {
    std::experimental::net::io_context io_context;
    tcp_server server1(&io_context);
    udp_server server2(&io_context);
    io_context.run();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch(std::bad_weak_ptr& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
