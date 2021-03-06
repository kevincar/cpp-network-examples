#include <experimental/net>
#include <iostream>
#include <chrono>

using std::experimental::net::ip::tcp;

int main(int argc, char* argv[])
{
  try {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <host>" << std::endl;
      return 1;
    }

    std::experimental::net::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

    tcp::socket socket(io_context);
    std::experimental::net::connect(socket, endpoints);

    bool done = false;
    while(!done) {
      std::array<char, 128> buffer;
      std::error_code ec;
      size_t len = socket.read_some(std::experimental::net::buffer(buffer), ec);

      if (ec == std::experimental::net::error::eof) {
        done = true;
      } else if(ec) {
        throw std::system_error(ec);
      }

      std::cout.write(buffer.data(), len);
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
