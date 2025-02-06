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
    SetThreadDescription((HANDLE)guiThread.native_handle(), L"GuiThread");

    std::thread networkThread(&UDPServer::Start, std::ref(UDPServer::GetInstance()));
    SetThreadDescription((HANDLE)networkThread.native_handle(), L"NetworkThread");



    networkThread.join();
    guiThread.join();

    return 0;
}