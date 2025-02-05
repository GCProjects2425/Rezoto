#pragma once
#include "Singleton.h"
#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define BUFLEN 512
#define PORT 8888

class UDPServer : public Singleton<UDPServer>
{
	friend class Singleton<UDPServer>;
public:
    UDPServer();
    ~UDPServer();

    void Start();
    void SendMessageToSelf(const std::string& message);


private:
    WSADATA wsa{};
    SOCKET server_socket = 0;
    sockaddr_in server{}, client{};
    bool exitRequested = false;
};