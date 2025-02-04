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
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);
    m_isConnected = true;
}

void UDPClient::Run()
{
    while (true) {
        /*char message[BUFLEN];
        cout << "Enter message: ";
        cin.getline(message, BUFLEN);

        // send the message
        if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
            cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        // receive a reply and print it
        // clear the answer by filling null, it might have previously received data
        char answer[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int slen = sizeof(sockaddr_in);
        int answer_length;
        if ((answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
            cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        cout << "Server's response: " << answer << "\n";*/
        if (m_isConnected) 
        {

        }
    }
}
