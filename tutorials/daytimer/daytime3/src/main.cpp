#include <ctime>
#include <experimental/net>
#include <iostream>

using std::experimental::net::ip::tcp;

std::string make_daytime_string() {
  using namespace std;
  time_t now = time(NULL);
  return ctime(&now);
}

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
    tcp_server server(&io_context);
    io_context.run();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch(std::bad_weak_ptr& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
