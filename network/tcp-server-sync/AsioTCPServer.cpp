/// \file   AsioTCPServer.cpp
/// \brief  Daytime.2 tutorial
#include "AsioCommon.h"

#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;

namespace {
constexpr char LOCALHOST[]{"127.0.0.1"};
constexpr unsigned short DAYTIME_PORT{13};
}  // namespace

/// Daytime.2 accepts connections on localhost
/// @note: Must run as root (port 13 is privileged)
int tcpDaytimeServerSynchronous() {
    try {
        asio::io_context asioContext;

        tcp::acceptor acceptor(
                asioContext, tcp::endpoint(asio::ip::make_address(LOCALHOST), DAYTIME_PORT));

        for (;;) {
            tcp::socket socket(asioContext);
            acceptor.accept(socket);

            std::string message = makeDaytimeResponse();

            asio::error_code ignoredError;
            asio::write(socket, asio::buffer(message), ignoredError);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

///
int main() {
    tcpDaytimeServerSynchronous();
}
