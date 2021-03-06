/// \file   AsioTCPClient.cpp
/// \brief  Daytime.1 tutorial
#include <array>
#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;

constexpr char DAYTIMER[]{"time.nist.gov"};

/// Daytime.1
int tcpDaytimeClientSynchronous(const char* serverAddr) {
    try {
        asio::io_context asioContext;
        tcp::resolver resolver(asioContext);
        tcp::resolver::results_type endpoints = resolver.resolve(serverAddr, "daytime");

        tcp::socket socket(asioContext);
        asio::connect(socket, endpoints);

        for (;;) {
            std::array<char, 128> buf{};
            asio::error_code error;
            auto len = socket.read_some(asio::buffer(buf), error);
            std::cout << len << " bytes returned from socket" << std::endl;

            if (error == asio::error::eof) {
                std::cout << "Connection closed by peer" << std::endl;
                break;
            } else if (error) {
                throw asio::system_error(error);
            }

            std::cout << "Resolved " << serverAddr << ", result: " << std::endl;
            std::cout.write(buf.data(), len);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

///
int main(int argc, char** argv) {

    if (argc > 1) {
        tcpDaytimeClientSynchronous(*++argv);
    } else {
        tcpDaytimeClientSynchronous(DAYTIMER);
    }
}
