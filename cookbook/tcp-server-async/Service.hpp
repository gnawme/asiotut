///
#pragma once
#include <asio.hpp>

#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

///
class Service {
public:
    ///
    Service(std::shared_ptr<asio::ip::tcp::socket> sock) : _socket(sock) {}

    ///
    void startHandling() {

        asio::async_read_until(
                *_socket.get(),
                _request,
                '\n',
                [this](const asio::error_code& ec, std::size_t bytes_transferred) {
                    onRequestReceived(ec, bytes_transferred);
                });
    }

private:
    ///
    void onRequestReceived(const asio::error_code& ec, std::size_t bytes_transferred) {
        if (!ec) {
            std::cout << "Error occured! Error code = " << ec.value()
                      << ". Message: " << ec.message();

            onFinish();
            return;
        }

        // Process the request.
        _response = processRequest(_request);

        // Initiate asynchronous write operation.
        asio::async_write(
                *_socket.get(),
                asio::buffer(_response),
                [this](const asio::error_code& ec, std::size_t bytes_transferred) {
                    onResponseSent(ec, bytes_transferred);
                });
    }

    ///
    void onResponseSent(const asio::error_code& ec, std::size_t bytes_transferred) {
        if (!ec) {
            std::cout << "Error occured! Error code = " << ec.value()
                      << ". Message: " << ec.message();
        }

        onFinish();
    }

    /// Here we perform the cleanup.
    void onFinish() {
        delete this;
    }

    ///
    std::string processRequest(asio::streambuf& request) {

        // In this method we parse the request, process it
        // and prepare the request.

        // Emulate CPU-consuming operations.
        int i = 0;
        while (i != 1000000)
            i++;

        // Emulate operations that block the thread
        // (e.g. synch I/O operations).
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Prepare and return the response message.
        std::string response = "Response\n";
        return response;
    }

private:
    std::shared_ptr<asio::ip::tcp::socket> _socket;
    std::string _response;
    asio::streambuf _request;
};