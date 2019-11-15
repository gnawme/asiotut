/// \file   AsioTut.cpp
/// \brief  Omnibus for ASIO tutorials
#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

using namespace std::chrono_literals;
using namespace std::placeholders;
using SteadyTimer = asio::basic_waitable_timer<std::chrono::steady_clock>;

///
void handler(const asio::error_code& error) {
    std::cout << "Hello, world!" << std::endl;
}

///
void print(const asio::error_code& error, SteadyTimer* timer, int* count) {
    if (*count < 5) {
        std::cout << *count << std::endl;
        ++(*count);
        timer->expires_at(timer->expiry() + 1s);
        timer->async_wait(std::bind(print, _1, timer, count));
    }
}

///
int timerAsynchronous() {
    std::cout << "Asynchronous timer" << std::endl;
    asio::io_context asioContext;
    SteadyTimer dtimer(asioContext, 5s);
    dtimer.async_wait(&handler);

    asioContext.run();
}

///
int timerBound() {
    std::cout << "Timer with bound arguments" << std::endl;
    int count = 0;
    asio::io_context asioContext;
    SteadyTimer timer(asioContext, 1s);
    timer.async_wait(std::bind(print, _1, &timer, &count));

    asioContext.run();

    std::cout << "Final count is " << count << std::endl;

    return 0;
}

///
int timerSynchronous() {
    std::cout << "Synchronous timer" << std::endl;
    asio::io_context asioContext;
    SteadyTimer dtimer(asioContext, 5s);
    dtimer.wait();

    std::cout << "Hello, world!" << std::endl;

    return 0;
}

///
int main() {
    timerSynchronous();
    timerAsynchronous();
    timerBound();
}