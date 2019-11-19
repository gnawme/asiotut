/// \file   AsioComboServer.cpp
/// \brief  Daytime.7 tutorial
#include "AsioTCPServer.h"
#include "AsioUDPServer.h"

///
int main(int argc, char** argv) {
    try {
        asio::io_context asioContext;
        AsioTCPServer tcpServer(asioContext);
        AsioUDPServer udpServer(asioContext);
        asioContext.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
