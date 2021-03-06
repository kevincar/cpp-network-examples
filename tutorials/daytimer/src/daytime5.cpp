#include <ctime>
#include <experimental/net>
#include <iostream>
#include <chrono>

using std::experimental::net::ip::udp;

std::string make_daytime_string() {
  using namespace std;
  time_t now = time(NULL);
  return ctime(&now);
}

int main(int argc, char* argv[])
{
  try {

    std::experimental::net::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));

    bool done = false;
    while(!done) {
      std::array<char, 1> recv_buf;
      udp::endpoint remote_endpoint;
      socket.receive_from(
          std::experimental::net::buffer(recv_buf),
          remote_endpoint
          );

      std::string message = make_daytime_string();

      std::error_code error;
      socket.send_to( std::experimental::net::buffer(message), remote_endpoint,
          0, error);
      if(!!error) {
        done = true;
      }
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
