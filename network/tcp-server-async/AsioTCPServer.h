/// \file   AsioTCPServer.h
/// \brief  Daytime.3 implementation
#pragma once

#include <asio.hpp>
#include <ctime>
#include <functional>
#include <memory>

using asio::ip::tcp;
using namespace std::placeholders;

namespace {
constexpr char LOCALHOST[]{"127.0.0.1"};
constexpr unsigned short DAYTIME_PORT{13};

/// Emulates the response of a daytime server
std::string makeDaytimeResponse() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}
}  // namespace

///
class AsioTCPConnection : public std::enable_shared_from_this<AsioTCPConnection> {
public:
    using ConnectionPtr = std::shared_ptr<AsioTCPConnection>;

    static ConnectionPtr create(asio::io_context& asioContext) {
        return ConnectionPtr(new AsioTCPConnection(asioContext));
    }

    tcp::socket& socket() {
        return _socket;
    }

    void start() {
        _message = makeDaytimeResponse();

        asio::async_write(
                _socket,
                asio::buffer(_message),
                std::bind(&AsioTCPConnection::handleWrite, shared_from_this(), _1, _2));
    }

private:
    AsioTCPConnection(asio::io_context& asioContext) : _socket(asioContext) {}

    void handleWrite(const asio::error_code&, size_t) {}

    tcp::socket _socket;
    std::string _message;
};

///
class AsioTCPServer {
public:
    AsioTCPServer(asio::io_context& asioContext)
            : _acceptor(
                      asioContext,
                      tcp::endpoint(asio::ip::make_address(LOCALHOST), DAYTIME_PORT)) {
        startAccept();
    }

private:
    void startAccept() {
        AsioTCPConnection::ConnectionPtr newConnection =
                AsioTCPConnection::create(_acceptor.get_executor().context());

        _acceptor.async_accept(
                newConnection->socket(),
                std::bind(&AsioTCPServer::handleAccept, this, newConnection, _1));
    }

    void
    handleAccept(AsioTCPConnection::ConnectionPtr newConnection, const asio::error_code& error) {
        if (!error) {
            newConnection->start();
        }

        startAccept();
    }

    tcp::acceptor _acceptor;
};
