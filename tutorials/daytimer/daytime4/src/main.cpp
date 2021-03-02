#include <experimental/net>
#include <iostream>
#include <chrono>

using std::experimental::net::ip::udp;

int main(int argc, char* argv[])
{
  try {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <host>" << std::endl;
      return 1;
    }

    std::experimental::net::io_context io_context;
    udp::resolver resolver(io_context);
    udp::endpoint receiver_endpoint = *resolver.resolve(udp::v4(), argv[1],
        "daytime").begin();

    udp::socket socket(io_context);
    socket.open(udp::v4());

    std::array<char, 128> send_buf = {{0}};
    socket.send_to(std::experimental::net::buffer(send_buf),
        receiver_endpoint);

    std::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        std::experimental::net::buffer(recv_buf),
        sender_endpoint
        );

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
