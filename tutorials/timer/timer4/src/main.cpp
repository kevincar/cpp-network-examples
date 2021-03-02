#include <experimental/net>
#include <iostream>
#include <chrono>
#include <functional>

class printer {
public:
  printer(std::experimental::net::io_context* io) : timer_(*io, std::chrono::seconds(1)), count_(0) {
    this->timer_.async_wait(std::bind(&printer::print, this));
  }

  ~printer() {
    std::cout << "Final count is " << this->count_ << std::endl;
  }

  void print() {
    if (this->count_ < 5) {
      std::cout << this->count_ << std::endl;
      ++this->count_;

      this->timer_.expires_at(this->timer_.expiry() + std::chrono::seconds(1));
      this->timer_.async_wait(std::bind(&printer::print, this));
    }
  }
private:
  int count_;
  std::experimental::net::steady_timer timer_;
};

int main(int argc, char* argv[]) {
  std::experimental::net::io_context io;
  printer p(&io);
  io.run();
	return 0;
}
