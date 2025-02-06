#include "UDPClient.h"

UDPClient::UDPClient() {
    WSAData wsa;
    std::cout << "Initializing Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed. Error Code: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    clientSocket = socket(AF_INET, SOCK_DGRAM, 17);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed. Error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    // Liaison du socket pour l'écoute des messages (évite l'erreur 10022)
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = INADDR_ANY;  // Écoute sur toutes les interfaces réseau
    clientAddr.sin_port = htons(0);           // Laisser le système choisir un port libre

    if (bind(clientSocket, (sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    std::cout << "UDP Client initialized successfully.\n";
}

UDPClient::~UDPClient() {
    running = false;
    closesocket(clientSocket);
    WSACleanup();
}

void UDPClient::SendMessage(const std::string& message) {
    int sendResult = sendto(clientSocket, message.c_str(), message.length(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));

    if (sendResult == SOCKET_ERROR) {
        std::cerr << "sendto() failed. Error: " << WSAGetLastError() << std::endl;
    }
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
            if (error == WSAEWOULDBLOCK) {
                // Pas de message disponible, on attend pour éviter de surcharger le CPU
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }
            else {
                std::cerr << "recvfrom() failed. Error: " << error << std::endl;
                break;
            }
        }

        // Affichage du message reçu
        std::string message(buffer, recvLen);
        std::cout << "Server: " << message << std::endl;
    }
}
