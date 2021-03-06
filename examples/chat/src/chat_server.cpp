#include <deque>
#include <iostream>
#include <list>
#include <set>
#include "experimental/net"
#include "chat_message.hpp"

using std::experimental::net::ip::tcp;

class chat_participant {
public:
  virtual ~chat_participant() {}
  virtual void deliver(chat_message const& msg) = 0;
};

class chat_room {
public:
  void join(std::shared_ptr<chat_participant> participant) {
    this->participants_.insert(participant);
    for (auto msg : this->recent_msgs_) {
      participant->deliver(msg);
    }
  }

  void leave(std::shared_ptr<chat_participant> participant) {
    this->participants_.erase(participant);
  }

  void deliver(chat_message const& msg) {
    this->recent_msgs_.push_back(msg);
    while (this->recent_msgs_.size() > this->kMaxRecentMsgs) {
      this->recent_msgs_.pop_front();
    }

    for (auto participant : this->participants_) {
      participant->deliver(msg);
    }
  }

private:
  std::set<std::shared_ptr<chat_participant>> participants_;
  int const kMaxRecentMsgs = 100;
  std::deque<chat_message> recent_msgs_;
};

class chat_session : public chat_participant, public std::enable_shared_from_this<chat_session> {
public:
  chat_session(tcp::socket socket, chat_room* room) :
    socket_(std::move(socket)), room_(room) {}

  void start() {
    this->room_->join(shared_from_this());
    this->do_read();
  }

  void deliver(chat_message const& msg) {
    bool write_in_progress = !this->write_msgs_.empty();
    this->write_msgs_.push_back(msg);
    if (!write_in_progress) {
      this->do_write();
    }
  }

private:
  void do_read() {
    auto handler = std::bind(&chat_session::read_handler,
        this->shared_from_this(), std::placeholders::_1, std::placeholders::_2);

    std::experimental::net::async_read(this->socket_,
        std::experimental::net::buffer(this->read_msg_.data()), handler);
  }

  void read_handler(std::error_code ec, std::size_t length) {
    if(!ec && this->read_msg_.check_header()) {
      this->room_->deliver(this->read_msg_);
      this->do_read();
    } else {
      this->room_->leave(this->shared_from_this());
    }
  }

  void do_write() {
    auto handler = std::bind(&chat_session::write_handler,
        this->shared_from_this(), std::placeholders::_1, std::placeholders::_2);

    std::experimental::net::async_write(this->socket_,
        std::experimental::net::buffer(this->write_msgs_.front().data()),
        handler);
  }

  void write_handler(std::error_code ec, std::size_t length) {
    if (!ec) {
      this->write_msgs_.pop_front();
      if (!this->write_msgs_.empty()) {
        this->do_write();
      }
    } else {
      this->room_->leave(this->shared_from_this());
    }
  }

  tcp::socket socket_;
  chat_room* room_;
  chat_message read_msg_;
  std::deque<chat_message> write_msgs_;
};

class chat_server {
public:
  chat_server(std::experimental::net::io_context* io_context, tcp::endpoint
      const& endpoint) : acceptor_(*io_context, endpoint) {
    this->do_accept();
  }

private:
  void do_accept() {
    auto handler = std::bind(&chat_server::accept_handler, this,
        std::placeholders::_1, std::placeholders::_2);
    this->acceptor_.async_accept(handler);
  }

  void accept_handler(std::error_code ec, tcp::socket socket) {
    if (!ec) {
      std::make_shared<chat_session>(std::move(socket), &this->room_)->start();
    }

    this->do_accept();
  }

  tcp::acceptor acceptor_;
  chat_room room_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc < 2) {
      std::cout << "Usage: chat_server <port> [<port> ...]" << std::endl;
      return 1;
    }

    std::experimental::net::io_context io_context;

    std::list<chat_server> servers;
    for (int i = 1; i < argc; ++i) {
      std::string port_str(argv[i]);
      int port = std::stoi(port_str);
      tcp::endpoint endpoint(tcp::v4(), port);
      servers.emplace_back(&io_context, endpoint);
    }

    io_context.run();
  }
  catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
