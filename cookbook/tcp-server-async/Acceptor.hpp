///
#pragma once
#include "Service.hpp"

#include <asio.hpp>
#include <iostream>

class Acceptor {
public:
    Acceptor(asio::io_context& asioContext, unsigned short tcpPort)
            : _asioContext(asioContext)
            , _acceptor(_asioContext, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), tcpPort))
            , _isStopped(false) {}

    // start accepting incoming connection requests.
    void start() {
        _acceptor.listen();
        initAccept();
    }

    // stop accepting incoming connection requests.
    void stop() {
        _isStopped.store(true);
    }

private:
    void initAccept() {
        std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(_asioContext));

        _acceptor.async_accept(*sock.get(), [this, sock](const asio::error_code& error) {
            onAccept(error, sock);
        });
    }

    void onAccept(const asio::error_code& ec, std::shared_ptr<asio::ip::tcp::socket> sock) {
        if (!ec) {
            (new Service(sock))->startHandling();
        } else {
            std::cout << "Error occured! Error code = " << ec.value()
                      << ". Message: " << ec.message();
        }

        // Init next async accept operation if
        // acceptor has not been stopped yet.
        if (!_isStopped.load()) {
            initAccept();
        } else {
            // stop accepting incoming connections
            // and free allocated resources.
            _acceptor.close();
        }
    }

private:
    asio::io_context& _asioContext;
    asio::ip::tcp::acceptor _acceptor;
    std::atomic<bool> _isStopped;
};