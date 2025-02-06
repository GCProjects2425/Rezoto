#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include <iostream>
#include <winsock2.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 512

class UDPClient {
public:
    UDPClient();
    ~UDPClient();

    void SendMessage(const std::string& message);
    void StartReceiving();

private:
    void ReceiveMessages();

    SOCKET clientSocket;
    sockaddr_in serverAddr;
    bool running;
};

#endif
