/// \file   AsioTimers.cpp
/// \brief  Omnibus for ASIO tutorials
#include "AsioTimers.h"

#include <thread>

/// Worker for async thread
void handler(const asio::error_code& error) {
    std::cout << "Hello, world!" << std::endl;
}

/// Worker for for std::bind example
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

    return 0;
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

/// Timer.5
int timerMultithreaded() {
    std::cout << "Multithreaded timer" << std::endl;
    asio::io_context asioContext;
    PrintStrand print(asioContext);
    std::thread asioThread([&asioContext] { asioContext.run(); });
    asioContext.run();
    asioThread.join();

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
    timerMultithreaded();
}
