#include "UDPClient.h"

#include <iostream>

#define BUFLEN 0xFFF  // max length of answer - header datas
#define SERVER /*"10.1.40.125"*/"127.0.0.1"
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
	shutdown(client_socket, SD_SEND);
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
	PushMessage(Message::Connect, "Salut");
	m_isConnected = true;
}

void UDPClient::Run()
{
	char answer[BUFLEN] = {};
	int slen = sizeof(sockaddr_in);
	while (true) {
		if (m_isConnected) {
			// Envoi d'un message au serveur
			std::shared_ptr<Message> messageToSend = nullptr;
			{
				std::lock_guard<std::mutex> lock(queueMutex);
				if (!m_MessagesToSend.empty()) {
					messageToSend = std::move(m_MessagesToSend.front());
					m_MessagesToSend.pop();
				}
			}

			if (messageToSend) {
				std::string serializedMessage = messageToSend->toString();
				if (sendto(client_socket, serializedMessage.c_str(), serializedMessage.size(), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
				{
					std::cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
				}
#ifdef _DEBUG
				else
				{
					std::cout << "Message sent to server: " << serializedMessage << "\n";
				}
#endif
			}

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

			if (message_len < BUFLEN)
			{
				answer[message_len] = '\0'; // Assurer que la chaîne est terminée
#ifdef _DEBUG
				std::cout << "Message received from server: " << answer << "\n";
#endif
				std::shared_ptr<Message> messageReceived(Message::fromString(answer));
				m_MessagesReceived.push(std::move(messageReceived));
			}
		}
	}
}

void UDPClient::PushMessage(Message::MessageType type, std::string message)
{
	std::lock_guard<std::mutex> lock(queueMutex);
	m_MessagesToSend.push(std::make_shared<Message>(type, std::move(message)));
}

std::shared_ptr<Message> UDPClient::PopReceivedMessage()
{
	std::lock_guard<std::mutex> lock(queueMutex);
	std::shared_ptr<Message> lastMessage = nullptr;
	if (!m_MessagesToSend.empty()) {
		lastMessage = std::move(m_MessagesToSend.front());
		m_MessagesToSend.pop();
	}
	return lastMessage;
}

bool UDPClient::IsEmpty() {
	std::lock_guard<std::mutex> lock(queueMutex);
	return m_MessagesToSend.empty();
}