#include <ctime>
#include <experimental/net>
#include <iostream>

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

int main(int argc, char* argv[])
{
  try {
    std::experimental::net::io_context io_context;
    udp_server server(&io_context);
    io_context.run();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch(std::bad_weak_ptr& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
