#pragma once
#include "Singleton.h"
#include "Message.h"
#include <iostream>
#include <winsock2.h>
#include <queue>
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
    void SendMessageToClient(std::shared_ptr<Message> message);

    void PushMessage(Message::MessageType type, std::string message, std::string ip, int port);
    std::shared_ptr<Message> PopReceivedMessage();
    bool IsEmpty();
private:
    WSADATA wsa{};
    SOCKET server_socket = 0;
    sockaddr_in server{}, client{};
    std::queue<std::shared_ptr<Message>> m_MessagesToSend;
    std::queue<std::shared_ptr<Message>> m_MessagesReceived;
    std::mutex queueMutex;

    bool exitRequested = false;
};