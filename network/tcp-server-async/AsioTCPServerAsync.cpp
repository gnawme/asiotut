/// \file   AsioTCPServerAsync.cpp
/// \brief  Daytime.3 tutorial
#include "AsioTCPServer.h"

#include <iostream>
#include <string>

using asio::ip::tcp;

///
int main() {
    try {
        asio::io_context asioContext;
        AsioTCPServer server(asioContext);
        asioContext.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
