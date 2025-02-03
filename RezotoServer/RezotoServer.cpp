// Ici c'est le serveur
//

#include <iostream>
#include <mutex>
#include <functional>

#include "UDPServer.h"
#include "GameServerGUI.h"   

int main() {
    system("title UDP Server");


    HINSTANCE hInstance = GetModuleHandle(NULL);
    GameServerGUI gui(hInstance);
    std::thread guiThread(std::bind(&GameServerGUI::Run, &gui));

    UDPServer udpServer;
    std::thread networkThread(std::bind(&UDPServer::Start, &udpServer));

    networkThread.join();
    guiThread.join();

    return 0;
}