#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8888
#define BUFFER_SIZE 512

class UDPServer {
public:
    static UDPServer& GetInstance();  // Singleton pour obtenir une instance unique

    void Start();
    void SendMessageToClient(const std::string& message, sockaddr_in& clientAddr);

private:
    UDPServer();
    ~UDPServer();

    void ReceiveMessages();

    SOCKET serverSocket;
    sockaddr_in serverAddr;
    std::vector<sockaddr_in> clients;
    std::mutex clientsMutex;
    bool running;
};

#endif
