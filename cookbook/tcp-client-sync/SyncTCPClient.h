/// \file   SyncTCPClient.h
/// \brief  Synchronous TCP client
#pragma once
#include <asio.hpp>
#include <sstream>
#include <string>

using asio::ip::tcp;

///
class SyncTCPClient {
public:
    ///
    SyncTCPClient(const char* ipAddress, unsigned short port)
            : _endpoint(asio::ip::make_address(ipAddress), port), _socket(_ioService) {}

    ///
    void connect() {
        _socket.connect(_endpoint);
    }

    ///
    void close() {
        _socket.shutdown(tcp::socket::shutdown_both);
        _socket.close();
    }

    ///
    std::string emulateLongComputationOp(unsigned int duration) {
        constexpr char OPSTR[]{"EMULATE_LONG_COMP_OP "};

        std::stringstream ss;
        ss << OPSTR << duration << '\n';
        sendRequest(ss.str());

        return receiveResponse();
    }

private:
    ///
    std::string receiveResponse() {
        asio::streambuf buf;
        asio::read_until(_socket, buf, '\n');

        std::istream input(&buf);

        std::string response;
        std::getline(input, response);

        return response;
    }

    ///
    void sendRequest(const std::string& request) {
        asio::write(_socket, asio::buffer(request));
    }

    tcp::endpoint _endpoint;
    asio::io_service _ioService;
    tcp::socket _socket;
};