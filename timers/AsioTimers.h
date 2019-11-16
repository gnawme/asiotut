/// \file   AsioTimers.h
/// \brief  Omnibus for ASIO tutorials
#pragma once
#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

using SteadyTimer = asio::basic_waitable_timer<std::chrono::steady_clock>;
using namespace std::chrono_literals;
using namespace std::placeholders;

/// Class for bound member function example
class Print {
public:
    ///
    Print(asio::io_context& context) : _asioContext(context), _timer(context, 5s) {
        _timer.async_wait(std::bind(&Print::print, this));
    }

    ///
    ~Print() {
        std::cout << "The final count is " << _count << std::endl;
    }

    ///
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

/// Class for multithreaded timer example
class PrintStrand {
public:
    ///
    PrintStrand(asio::io_context& context)
            : _asioContext(context), _strand(context), _timer1(context, 5s), _timer2(context, 5s) {
        _timer1.async_wait(asio::bind_executor(_strand, std::bind(&PrintStrand::print1, this)));
        _timer1.async_wait(asio::bind_executor(_strand, std::bind(&PrintStrand::print2, this)));
    }

    ///
    ~PrintStrand() {
        std::cout << "The final count is " << _count << std::endl;
    }

    ///
    void print1() {
        if (_count < 10) {
            std::cout << "Timer 1: " << _count << std::endl;
            ++_count;
            _timer1.expires_at(_timer1.expiry() + 1s);
            _timer1.async_wait(asio::bind_executor(_strand, std::bind(&PrintStrand::print1, this)));
        }
    }

    void print2() {
        if (_count < 10) {
            std::cout << "Timer 2: " << _count << std::endl;
            ++_count;
            _timer2.expires_at(_timer1.expiry() + 1s);
            _timer2.async_wait(asio::bind_executor(_strand, std::bind(&PrintStrand::print2, this)));
        }
    }

private:
    asio::io_context& _asioContext;
    asio::io_context::strand _strand;
    SteadyTimer _timer1;
    SteadyTimer _timer2;
    int _count{0};
};
