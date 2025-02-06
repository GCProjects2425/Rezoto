#include "UDPClient.h"

UDPClient::UDPClient() {
    WSAData wsa;
    std::cout << "Initializing Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed. Error Code: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed. Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);
}

UDPClient::~UDPClient() {
    running = false;
    closesocket(clientSocket);
    WSACleanup();
}

void UDPClient::SendMessage(const std::string& message) {
    sendto(clientSocket, message.c_str(), message.length(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));
}

void UDPClient::StartReceiving() {
    running = true;
    std::thread recvThread(&UDPClient::ReceiveMessages, this);
    recvThread.detach();
}

void UDPClient::ReceiveMessages() {
    char buffer[BUFFER_SIZE];
    sockaddr_in fromAddr;
    int fromLen = sizeof(fromAddr);

    while (running) {
        memset(buffer, 0, BUFFER_SIZE);
        int recvLen = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (sockaddr*)&fromAddr, &fromLen);

        if (recvLen == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK) {
                std::cerr << "recvfrom() failed. Error: " << error << std::endl;
            }
            continue;
        }

        std::string message(buffer, recvLen);
        std::cout << "Server: " << message << std::endl;
    }
}
