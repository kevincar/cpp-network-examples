#include <deque>
#include <iostream>
#include <thread>
#include "experimental/net"
#include "chat_message.hpp"

using std::experimental::net::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
  chat_client(std::experimental::net::io_context* io_context,
      tcp::resolver::results_type const& endpoints) :
    io_context_(io_context),
    socket_(*io_context) {
    this->do_connect(endpoints);
  }

  void write(const chat_message& msg) {
    std::experimental::net::post(*this->io_context_,
        [this, msg]() {
          bool write_in_progress = !this->write_msgs_.empty();
          this->write_msgs_.push_back(msg);
          if (!write_in_progress) {
            this->do_write();
            } else {
            std::cout << "Hold: writing in progress..." << std::endl;
            }
        });
  }

  void close() {
    std::experimental::net::post(*this->io_context_, [this]() { this->socket_.close(); });
  }

private:
  void do_connect(tcp::resolver::results_type const& endpoints) {
    std::experimental::net::async_connect(this->socket_, endpoints,
        [this](std::error_code ec, tcp::endpoint) {
          if (!ec) {
            this->do_read();
          }
        });
  }

  void do_read() {
    std::experimental::net::async_read(this->socket_,
        std::experimental::net::buffer(this->read_msg_.data()),
        [this](std::error_code ec, std::size_t /*length*/) {
          if (!ec && this->read_msg_.check_header()) {
            std::cout << this->read_msg_.body() << std::endl;
            this->do_read();
          } else {
            this->socket_.close();
          }
        });
  }

  void do_write() {
    std::experimental::net::async_write(this->socket_,
        std::experimental::net::buffer(this->write_msgs_.front().data(),
          this->write_msgs_.front().length()),
        [this](std::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            this->write_msgs_.pop_front();
            if (!this->write_msgs_.empty()) {
              this->do_write();
              }
          } else {
            this->socket_.close();
          }
        });
  }

private:
  std::experimental::net::io_context* io_context_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    std::experimental::net::io_context io_context;

    tcp::resolver resolver(io_context);
    std::string host(argv[1]);
    std::string port(argv[2]);
    auto endpoints = resolver.resolve(host, port);
    chat_client c(&io_context, endpoints);

    std::thread t([&io_context](){ io_context.run(); });

    std::string line;
    std::getline(std::cin, line);
    while(line != "exit") {
      chat_message msg;
      msg.assign(line);
      c.write(msg);
      std::getline(std::cin, line);
    }
    std::cout << "Closing..." << std::endl;

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
