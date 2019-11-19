/// \file   AsioUDPServer.cpp
/// \brief  Daytime.5 tutorial
#include <array>
#include <asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

using asio::ip::udp;

///
std::string makeDaytimeResponse() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

/// Daytime.5
int udpDaytimeServerSynchronous() {
    try {
        asio::io_context asioContext;

        udp::socket socket(asioContext, udp::endpoint(udp::v4(), 13));

        for (;;) {
            std::array<char, 1> receiveBuf;
            udp::endpoint remoteEndpoint;
            asio::error_code error;
            socket.receive_from(asio::buffer(receiveBuf), remoteEndpoint);

            std::string message = makeDaytimeResponse();

            asio::error_code ignoredError;
            socket.send_to(asio::buffer(message), remoteEndpoint, 0, ignoredError);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

///
int main(int argc, char** argv) {
    udpDaytimeServerSynchronous();
}
