#include <experimental/net>
#include <iostream>
#include <chrono>

void print(std::error_code const& e, std::experimental::net::steady_timer* t,
    int* count) {
  if (*count < 5) {
    std::cout << *count << std::endl;
    ++(*count);
    t->expires_at(t->expiry() + std::chrono::seconds(1));
    t->async_wait(std::bind(print, std::placeholders::_1, t, count));
  }
}

int main(int argc, char* argv[])
{
  std::experimental::net::io_context io;
  int count  = 0;
  std::experimental::net::steady_timer t(io, std::chrono::seconds(1));
  t.async_wait(std::bind(print, std::placeholders::_1, &t, &count));
  io.run();
  std::cout << "Final Cound: " << count << std::endl;
	return 0;
}
