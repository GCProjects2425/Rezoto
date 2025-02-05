#include <iostream>
#include <functional>

#include "GameClient.h"
#include "UDPClient.h"

int main(void)
{
    // Network thread
    std::thread networkThread(std::bind(&UDPClient::Run, UDPClient::GetInstance()));
    SetThreadDescription((HANDLE)networkThread.native_handle(), L"NetworkThread");

    return GameClient::GetInstance()->Run();
}
