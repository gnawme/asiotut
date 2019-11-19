/// \file   AsioUDPServerAsync.cpp
/// \brief  Daytime.6 tutorial
#include "AsioUDPServer.h"

///
int main(int argc, char** argv) {
    try {
        asio::io_context asioContext;
        AsioUDPServer server(asioContext);
        asioContext.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
