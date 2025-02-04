#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "Singleton.h"
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX   

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib") 
#pragma warning(disable:4996) 

#endif // UDPCLIENT_H

class UDPClient :
    public Singleton<UDPClient>
{
    friend class Singleton<UDPClient>;
public:
    UDPClient();
    ~UDPClient();

    void Connect(std::string ip, int port);
    void Run();
private:
    WSADATA ws{};
    SOCKET client_socket = 0;
    sockaddr_in server{};

    bool m_isConnected = 0;
};

