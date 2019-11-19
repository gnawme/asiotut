/// \file   AsioUDPServer.h
/// \brief  Daytime.6 classes
#pragma once

#include <array>
#include <asio.hpp>
#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using asio::ip::udp;
using namespace std::placeholders;

///
std::string makeDaytimeResponse() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

///
class AsioUDPServer {
public:
    AsioUDPServer(asio::io_context& asioContext)
            : _socket(asioContext, udp::endpoint(udp::v4(), 13)) {
        startReceive();
    }

private:
    void startReceive() {
        _socket.async_receive_from(
                asio::buffer(_receiveBuffer),
                _remoteEndpoint,
                std::bind(&AsioUDPServer::handleReceive, this, _1, _2));
    }

    void handleReceive(const asio::error_code& error, std::size_t) {
        if (!error) {
            std::cout << "Server received request, sending daytime response" << std::endl;
            std::shared_ptr<std::string> message(new std::string(makeDaytimeResponse()));

            _socket.async_send_to(
                    asio::buffer(*message),
                    _remoteEndpoint,
                    std::bind(&AsioUDPServer::handleSend, this, message, _1, _2));

            startReceive();
        }
    }

    void handleSend(std::shared_ptr<std::string>, const asio::error_code&, std::size_t) {}

    udp::socket _socket;
    udp::endpoint _remoteEndpoint;
    std::array<char, 1> _receiveBuffer;
};
