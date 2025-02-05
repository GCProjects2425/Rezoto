#include "UDPClient.h"

#include <iostream>

#define BUFLEN 512  // max length of answer
#define SERVER "10.1.40.125"
#define PORT 8888

UDPClient::UDPClient()
{
    std::cout << "Initialising Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        std::cout << "Failed. Error Code: " << WSAGetLastError() << "\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Initialised.\n";

    // create socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        std::cout << "socket() failed with error code: " << WSAGetLastError() << "\n";
        exit(EXIT_FAILURE);
    }

    memset((char*)&server, 0, sizeof(server));
}

UDPClient::~UDPClient()
{
    closesocket(client_socket);
    WSACleanup();
}

void UDPClient::Connect(std::string ip, int port)
{
    // setup address structure
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
    m_isConnected = true;
}

void UDPClient::Run()
{
    Connect(SERVER, PORT);

    char answer[BUFLEN] = {};
    sockaddr_in server;
    int slen = sizeof(sockaddr_in);

    while (true) {
        int answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen);
        if (answer_length == SOCKET_ERROR) {
            int errorCode = WSAGetLastError();
            if (errorCode == WSAEWOULDBLOCK) {
                continue; // Pas de données, on continue à écouter
            }
            std::cout << "recvfrom() failed with error code: " << errorCode << "\n";
            break;
        }


        answer[answer_length] = '\0'; // Assure que le message est bien terminé
        std::cout << "Server: " << answer << "\n";
    }
}
