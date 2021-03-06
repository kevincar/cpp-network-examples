#include <ctime>
#include <experimental/net>
#include <iostream>

using std::experimental::net::ip::tcp;

std::string make_daytime_string() {
  using namespace std;
  time_t now = time(NULL);
  return ctime(&now);
}

int main(int argc, char* argv[])
{
  try {

    std::experimental::net::io_context io_context;
    tcp::endpoint local_endpoint(tcp::v4(), 13);
    tcp::acceptor acceptor(io_context, local_endpoint);

    //tcp::resolver resolver(io_context);
    //tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

    bool done = false;
    while(!done) {
      tcp::socket socket = acceptor.accept();

      std::string message = make_daytime_string();

      std::error_code ec;
      size_t len = std::experimental::net::write(
          socket,
          std::experimental::net::buffer(message),
          ec
          );

      std::cout << "Wrote " << len << " bytes" << std::endl;

      if (!!ec) {
        std::cerr << "Error: " << ec.message() << std::endl;
      }
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
