#include <experimental/net>
#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

class printer {
public:
  printer(std::experimental::net::io_context* io)
    : strand_(std::experimental::net::strand<std::experimental::net::io_context::executor_type>(io->get_executor())),
      timer1_(*io, std::chrono::seconds(1)),
      timer2_(*io, std::chrono::seconds(1)),
      count_(0) {

    this->timer1_.async_wait(
        std::experimental::net::bind_executor(
          this->strand_,
          std::bind(&printer::print1, this))
          );
    this->timer2_.async_wait(
        std::experimental::net::bind_executor(
          this->strand_,
          std::bind(&printer::print2, this))
          );
  }

  ~printer() {
    std::cout << "Final count is " << this->count_ << std::endl;
  }

  void print1() {
    if (this->count_ < 10) {
      std::cout << "Timer 1: " << this->count_ << std::endl;
      ++this->count_;

      this->timer1_.expires_at(this->timer1_.expiry() + std::chrono::seconds(1));
      this->timer1_.async_wait(
          std::experimental::net::bind_executor(
            this->strand_,
            std::bind(&printer::print1, this))
            );
    }
  }

  void print2() {
    if (this->count_ < 10) {
      std::cout << "Timer 2: " << this->count_ << std::endl;
      ++this->count_;

      this->timer2_.expires_at(this->timer2_.expiry() + std::chrono::seconds(1));
      this->timer2_.async_wait(
          std::experimental::net::bind_executor(
            this->strand_,
            std::bind(&printer::print2, this))
            );
    }
  }

private:
  int count_;
  std::experimental::net::steady_timer timer1_;
  std::experimental::net::steady_timer timer2_;
  std::experimental::net::strand<std::experimental::net::io_context::executor_type>
    strand_;
};

int main(int argc, char* argv[]) {
  std::experimental::net::io_context io;
  printer p(&io);
  std::thread t([&]{
      printer p(&io);
      io.run();
      });
  io.run();
  t.join();
	return 0;
}
