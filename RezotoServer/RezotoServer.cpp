// Ici c'est le serveur
//

#include <iostream>
#include <mutex>
#include <functional>

#include "UDPServer.h"
#include "GameServerGUI.h"   
#include "GameManager.h"

int main() {
    system("title UDP Server");

    HINSTANCE hInstance = GetModuleHandle(NULL);
    GameServerGUI gui(hInstance);
    std::thread guiThread(std::bind(&GameServerGUI::Run, &gui));
    SetThreadDescription((HANDLE)guiThread.native_handle(), L"GuiThread");

    std::thread networkThread(std::bind(&UDPServer::Start, UDPServer::GetInstance()));
    SetThreadDescription((HANDLE)networkThread.native_handle(), L"NetworkThread");

    std::thread gameThread(std::bind(&GameManager::Run, GameManager::GetInstance()));
    SetThreadDescription((HANDLE)gameThread.native_handle(), L"GameThread");

    networkThread.join();
    guiThread.join();
	gameThread.join();

    return 0;
}