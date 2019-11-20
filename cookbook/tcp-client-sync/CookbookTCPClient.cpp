/// \file   CookbookTCPClient.cpp
/// \brief  Synchronous TCP client
#include "SyncTCPClient.h"

#include <iostream>

///
int main() {
    constexpr char LOCALHOST[]{"127.0.0.1"};
    constexpr unsigned int PORT{3333};

    try {
        SyncTCPClient client(LOCALHOST, PORT);

        client.connect();

        std::cout << "Sending request to server" << std::endl;
        std::string response = client.emulateLongComputationOp(10u);

        std::cout << "Response received: " << response << std::endl;
        client.close();
    } catch (std::system_error& e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
    }

    return 0;
}