/// \file   AsioUDPClient.cpp
/// \brief  Daytime.4 tutorial
#include <array>
#include <asio.hpp>
#include <iostream>

using asio::ip::udp;

constexpr char DAYTIMER[]{"pool.ntp.org"};

/// Daytime.4
int udpDaytimeClientSynchronous(const char* serverAddr) {
    try {
        asio::io_context asioContext;

        udp::resolver resolver(asioContext);
        udp::endpoint receiverEndpoint =
                *resolver.resolve(udp::v4(), serverAddr, "daytime").begin();

        std::cout << "Address resolved to " << receiverEndpoint.address() << ":"
                  << receiverEndpoint.port() << std::endl;

        udp::socket socket(asioContext);
        socket.open(udp::v4());

        std::cout << "Socket opened: " << std::boolalpha << socket.is_open() << std::endl;

        std::array<char, 1> sendBuf{{0}};
        auto sent = socket.send_to(asio::buffer(sendBuf), receiverEndpoint);
        std::cout << "Sent " << sent << " bytes to endpoint" << std::endl;

        std::array<char, 128> recvBuf{{0}};
        udp::endpoint senderEndpoint;
        size_t len = socket.receive_from(asio::buffer(recvBuf), senderEndpoint);
        std::cout << len << " bytes received" << std::endl;

        std::cout.write(recvBuf.data(), len);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

///
int main(int argc, char** argv) {

    if (argc > 1) {
        udpDaytimeClientSynchronous(*++argv);
    } else {
        udpDaytimeClientSynchronous(DAYTIMER);
    }
}
