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

    u_long mode = 1;  // 1 = non-bloquant, 0 = bloquant
    ioctlsocket(client_socket, FIONBIO, &mode);

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
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    if (connect(client_socket, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        std::cout << "connect() failed with error code: " << WSAGetLastError() << "\n";
        exit(EXIT_FAILURE);
    }
    m_isConnected = true;
}

void UDPClient::Run()
{
    char answer[BUFLEN] = {};
    int slen = sizeof(sockaddr_in);

    while (true) {
        if (m_isConnected)
        {
			//const char* message = "Hello from client!";
   //         if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
   //             std::cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
   //             exit(EXIT_FAILURE);
   //         }

            //int answer_length = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen);
            //if (answer_length == SOCKET_ERROR) {
            //    int errorCode = WSAGetLastError();
            //    if (errorCode == WSAEWOULDBLOCK) {
            //        continue; // Pas de données, on continue à écouter
            //    }
            //    std::cout << "recvfrom() failed with error code: " << errorCode << "\n";
            //    break;
            //}


            //answer[answer_length] = '\0'; // Assure que le message est bien terminé
            //std::cout << "Server: " << answer << "\n";

            int message_len;
            int slen = sizeof(sockaddr_in);
            if ((message_len = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
                int errorCode = WSAGetLastError();
                //cout << "recvfrom() failed with error code: " << errorCode << "\n";
                if (errorCode == WSAECONNRESET) {
                    std::cout << "Client forcibly closed the connection.\n";
                }
                continue;  // Continue la boucle au lieu d'exécuter `exit(0)`
            }

            // print details of the client/peer and the data received
            std::cout << "Received packet from " << inet_ntoa(server.sin_addr) << " " << ntohs(server.sin_port) << "\n";
            std::cout << "Data: " << answer << "\n";
        }
    }
}
