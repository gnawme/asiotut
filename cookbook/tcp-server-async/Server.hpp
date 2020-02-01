/// \file Server.hpp
#pragma once
#include "Acceptor.hpp"

#include <asio.hpp>
#include <cassert>

class Server {
public:
    Server() {
        _worker.reset(new asio::io_context::work(_asioContext));
    }

    // Start the server.
    void start(unsigned short port, unsigned int threadPoolSize) {

        assert(threadPoolSize > 0);

        // Create and start Acceptor.
        acc.reset(new Acceptor(_asioContext, port));
        acc->start();

        // Create specified number of threads and
        // add them to the pool.
        for (unsigned int i = 0; i < threadPoolSize; i++) {
            std::unique_ptr<std::thread> th(new std::thread([this]() { _asioContext.run(); }));

            m_thread_pool.push_back(std::move(th));
        }
    }

    // Stop the server.
    void stop() {
        acc->stop();
        _asioContext.stop();

        for (auto& th : m_thread_pool) {
            th->join();
        }
    }

private:
    asio::io_context _asioContext;
    std::unique_ptr<asio::io_context::work> _worker;
    std::unique_ptr<Acceptor> acc;
    std::vector<std::unique_ptr<std::thread>> m_thread_pool;
};