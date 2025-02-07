#include "UDPServer.h"
#include "Message.h"

//UDPServer& UDPServer::GetInstance() {
//    static UDPServer instance;
//    return instance;
//}

UDPServer::UDPServer() {
    // initialise winsock
    cout << "Initialising Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError() << "\n";
        exit(0);
    }
    cout << "Initialised.\n";

    // create a socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket: " << WSAGetLastError() << "\n";
        exit(EXIT_FAILURE);
    }
    cout << "Socket created.\n";
    u_long mode = 1;  // 1 = non-bloquant, 0 = bloquant

    ioctlsocket(server_socket, FIONBIO, &mode);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&mode, sizeof(mode));
    setsockopt(server_socket, SOL_SOCKET, SO_BROADCAST, (char*)&mode, sizeof(mode));
    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Bind failed with error code: " << WSAGetLastError() << "\n";
        exit(EXIT_FAILURE);
    }
    cout << "Bind done.\n";
}

UDPServer::~UDPServer() {
    shutdown(server_socket, SD_SEND);
    closesocket(server_socket);
    WSACleanup();
}

void UDPServer::Start()
{
    char answer[BUFLEN] = {};
    int slen = sizeof(sockaddr_in);

    while (!exitRequested) {
        std::shared_ptr<Message> messageToSend = nullptr;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (!m_MessagesToSend.empty()) {
                messageToSend = std::move(m_MessagesToSend.front());
                m_MessagesToSend.pop();
            }
        }

        if (messageToSend) {
            SendMessageToClient(std::move(messageToSend));
        }

        // Réception de la réponse du serveur
        int message_len;
        if ((message_len = recvfrom(server_socket, answer, BUFLEN, 0, (sockaddr*)&client, &slen)) == SOCKET_ERROR) {
            int errorCode = WSAGetLastError();
            if (errorCode == WSAECONNRESET)
            {
                cout << "Client forcibly closed the connection.";
            }
            if (errorCode == WSAEWOULDBLOCK) {
                continue; // Pas de données pour l'instant
            }
            std::cout << "recvfrom() failed with error code: " << errorCode << "\n";
            break;
        }

        if (message_len < BUFLEN)
        {
            answer[message_len] = '\0'; // Assurer que la chaîne est terminée
#ifdef _DEBUG
            cout << "Received packet from " << inet_ntoa(client.sin_addr) << " " << client.sin_port << "\n";
            cout << "Data: " << answer << "\n";
#endif
            std::shared_ptr<Message> messageReceived = make_shared<Message>(Message::fromString(answer));
            messageReceived->ip = inet_ntoa(client.sin_addr);
            messageReceived->port = client.sin_port;
            m_MessagesReceived.push(messageReceived);
			PushMessage(Message::MessageType::Ping, "Pong", messageReceived->ip, messageReceived->port);
        }

    }
}


void UDPServer::SendMessageToClient(std::shared_ptr<Message> message)
{
    sockaddr_in selfAddr;
    selfAddr.sin_family = AF_INET;
    selfAddr.sin_addr.s_addr = inet_addr(message->ip.c_str());  // Envoi à localhost        
    selfAddr.sin_port = message->port;  // Utilisation du même port que le serveur

    // Envoyer le message
    if (sendto(server_socket, message->toString().c_str(), message->toString().length(), 0, (sockaddr*)&selfAddr, sizeof(selfAddr)) == SOCKET_ERROR) {
        std::cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
    }
    else {
        std::cout << "Message sent to " << message->ip << ":" << std::to_string(message->port) << " -> " << message->message << "\n";
    }
}

void UDPServer::PushMessage(Message::MessageType type, std::string message, std::string ip, int port)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    m_MessagesToSend.push(std::make_shared<Message>(type, std::move(message), std::move(ip), port));
}

std::shared_ptr<Message> UDPServer::PopReceivedMessage()
{
    std::lock_guard<std::mutex> lock(queueMutex);
    std::shared_ptr<Message> lastMessage = nullptr;
    if (!m_MessagesReceived.empty()) {
        lastMessage = std::move(m_MessagesReceived.front());
        m_MessagesReceived.pop();
    }
    return lastMessage;
}

bool UDPServer::IsEmpty() {
    std::lock_guard<std::mutex> lock(queueMutex);
    return m_MessagesReceived.empty();
}