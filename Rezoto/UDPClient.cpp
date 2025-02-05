#include "UDPClient.h"

#include <iostream>

#define BUFLEN 512  // max length of answer
#define SERVER "127.0.0.1"
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
    server.sin_addr.s_addr = inet_addr(ip.c_str()); // Utiliser l'IP passée en paramètre

    // En UDP, pas besoin de `connect()`
    m_isConnected = true;
}

void UDPClient::Run()
{
    char answer[BUFLEN] = {};
    int slen = sizeof(sockaddr_in);
    Connect(SERVER, PORT);
    while (true) {
        if (true) {
            // Envoi d'un message au serveur
            const char* message = "Hello from client!";
            //if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR) {
            //    std::cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
            //    continue;
            //}
            //std::cout << "Message sent to server: " << message << "\n";

            // Réception de la réponse du serveur
            int message_len;
            if ((message_len = recvfrom(client_socket, answer, BUFLEN, 0, (sockaddr*)&server, &slen)) == SOCKET_ERROR) {
                int errorCode = WSAGetLastError();
                if (errorCode == WSAEWOULDBLOCK) {
                    continue; // Pas de données pour l'instant
                }
                std::cout << "recvfrom() failed with error code: " << errorCode << "\n";
                break;
            }

            answer[message_len] = '\0'; // Assurer que la chaîne est terminée
            std::cout << "Server: " << answer << "\n";
        }
    }
}
