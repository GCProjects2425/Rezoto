#include <iostream>
#include <functional>

#include "GameClient.h"
#include "UDPClient.h"

int main(void)
{
    system("title Le Rezoto c'est bon");

    // Network thread
    std::thread networkThread(std::bind(&UDPClient::Run, UDPClient::GetInstance()));
    SetThreadDescription((HANDLE)networkThread.native_handle(), L"NetworkThread");

    std::thread gameThread(std::bind(&GameClient::Run, GameClient::GetInstance()));
    SetThreadDescription((HANDLE)gameThread.native_handle(), L"GameThread");

    gameThread.join();
    networkThread.join();

    return 0;
}