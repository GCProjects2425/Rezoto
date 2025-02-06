#include "UDPServer.h"

UDPServer& UDPServer::GetInstance() {
    static UDPServer instance;
    return instance;
}

UDPServer::UDPServer() {
    WSAData wsa;
    std::cout << "Initializing Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed. Error Code: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed. Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    std::cout << "UDP Server started on port " << SERVER_PORT << std::endl;
}

UDPServer::~UDPServer() {
    running = false;
    closesocket(serverSocket);
    WSACleanup();
}

void UDPServer::Start() {
    running = true;
    ReceiveMessages();
}

void UDPServer::ReceiveMessages() {
    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr;
    int clientLen = sizeof(clientAddr);

    while (running) {
        memset(buffer, 0, BUFFER_SIZE);
        int recvLen = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (sockaddr*)&clientAddr, &clientLen);

        if (recvLen == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK) {
                std::cerr << "recvfrom() failed. Error: " << error << std::endl;
            }
            continue;
        }

        std::string message(buffer, recvLen);
        std::cout << "Received from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " -> " << message << std::endl;

        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(clientAddr);

        SendMessageToClient("Message received!", clientAddr);
    }
}

void UDPServer::SendMessageToClient(const std::string& message, sockaddr_in& clientAddr) {
    sendto(serverSocket, message.c_str(), message.length(), 0, (sockaddr*)&clientAddr, sizeof(clientAddr));
}
