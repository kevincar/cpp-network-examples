#include <experimental/net>
#include <iostream>
#include <chrono>

void print(std::error_code const& e) {
  std::cout << "Hello, World!" << std::endl;
}

int main(int argc, char* argv[])
{
  std::experimental::net::io_context io;
  std::experimental::net::steady_timer t(io, std::chrono::seconds(5));
  t.async_wait(&print);
  io.run();
	return 0;
}
