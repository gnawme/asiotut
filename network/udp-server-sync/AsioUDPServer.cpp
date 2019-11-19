/// \file   AsioUDPServer.cpp
/// \brief  Daytime.5 tutorial
#include "AsioCommon.h"

#include <array>
#include <asio.hpp>
#include <iostream>

using asio::ip::udp;

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
