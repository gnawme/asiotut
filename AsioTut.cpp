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
class Print {
public:
    Print(asio::io_context& context) : _asioContext(context), _timer(context, 5s) {
        _timer.async_wait(std::bind(&Print::print, this));
    }

    ~Print() {
        std::cout << "The final count is " << _count << std::endl;
    }

    void print() {
        if (_count < 5) {
            std::cout << _count << std::endl;
            ++(_count);
            _timer.expires_at(_timer.expiry() + 1s);
            _timer.async_wait(std::bind(&Print::print, this));
        }
    }

private:
    asio::io_context& _asioContext;
    SteadyTimer _timer;
    int _count{0};
};

///
void handler(const asio::error_code& error) {
    std::cout << "Hello, world!" << std::endl;
}

///
void print(const asio::error_code& error, SteadyTimer& timer, int* count) {
    if (*count < 5) {
        std::cout << *count << std::endl;
        ++(*count);
        timer.expires_at(timer.expiry() + 1s);
        timer.async_wait(std::bind(print, _1, std::ref(timer), count));
    }
}

/// Timer.2
int timerAsynchronous() {
    std::cout << "Asynchronous timer" << std::endl;
    asio::io_context asioContext;
    SteadyTimer dtimer(asioContext, 5s);
    dtimer.async_wait(&handler);

    asioContext.run();
}

/// Timer.3
int timerBound() {
    std::cout << "Timer with bound arguments" << std::endl;
    int count = 0;
    asio::io_context asioContext;
    SteadyTimer timer(asioContext, 1s);
    timer.async_wait(std::bind(print, _1, std::ref(timer), &count));

    asioContext.run();

    std::cout << "Final count is " << count << std::endl;

    return 0;
}

/// Timer.4
int timerBoundClass() {
    std::cout << "Timer with bound member function" << std::endl;
    asio::io_context asioContext;
    Print print(asioContext);
    asioContext.run();

    return 0;
}

/// Timer.1
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
    timerBoundClass();
}