#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "Singleton.h"
#include "Message.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX   

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#include <queue>

#endif // UDPCLIENT_H

class UDPClient :
    public Singleton<UDPClient>
{
    friend class Singleton<UDPClient>;
public:
    UDPClient();
    ~UDPClient();
    uint32_t LastMessageSequence;
    void Connect(std::string ip, int port, std::string username);
    void Run();

    void PushMessage(Message::MessageType type, std::string message);
    std::shared_ptr<Message> PopReceivedMessage();
    bool IsEmpty();
private:
	void PingServer();

    void ManageMessages();

    WSADATA ws{};
    SOCKET client_socket = 0;
    sockaddr_in server{};
    std::queue<std::shared_ptr<Message>> m_MessagesToSend;
    std::queue<std::shared_ptr<Message>> m_MessagesReceived;
    std::mutex queueMutex;

	time_t lastPing = 0;
    bool m_isConnected = 0;
};