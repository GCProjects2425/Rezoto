// Ici c'est le serveur
//

#include <iostream>
#include <mutex>
#include <functional>

#include "UDPServer.h"



int main() {
    system("title UDP Server");

    UDPServer udpServer;

    std::thread networkThread(std::bind(&UDPServer::Start, &udpServer));

    networkThread.join();
    return 0;
}