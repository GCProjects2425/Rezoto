#pragma once
#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 

#define BUFLEN 512
#define PORT 8888

class UDPServer
{
public:
    UDPServer();
    ~UDPServer();

    void Start();

private:
    WSADATA wsa{};
    SOCKET server_socket = 0;
    sockaddr_in server{}, client{};
    bool exitRequested = false;
};