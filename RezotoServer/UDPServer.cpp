#include "UDPServer.h"
#include "GameStatus.h"
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
	closesocket(server_socket);
	WSACleanup();
}

void UDPServer::Start() {

	GameStatus* gs = new GameStatus();
	gs->ballPos.x = 10;
	gs->ballPos.y = 11;

	gs->player1PaddlePos.x = 12;
	gs->player1PaddlePos.y = 13;

	gs->player2PaddlePos.x = 14;
	gs->player2PaddlePos.y = 15;
	SendMessageToSelf(gs->toString());

	while (!exitRequested) {
		cout << "Waiting for data...\n";
		char message[BUFLEN] = {};

		// try to receive some data, this is a blocking call
		int message_len;
		int slen = sizeof(sockaddr_in);
		if ((message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen)) == SOCKET_ERROR) {
			cout << "recvfrom() failed with error code: " << WSAGetLastError() << "\n";
			exit(0);
		}

		// print details of the client/peer and the data received
		cout << "Received packet from " << inet_ntoa(client.sin_addr) << " " << ntohs(client.sin_port) << "\n";
		cout << "Data: " << message << "\n";

		cout << "Enter response (exit to stop server process): ";
		cin.getline(message, BUFLEN);

		// reply to the client with the same data
		if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
			exit(EXIT_FAILURE);
		}

		//if(wsase)

		if (strcmp(message, "exit") == 0) {
			cout << "Exiting server...\n";
			exitRequested = true;
			break;
		}

	}
}
	void UDPServer::SendMessageToSelf(const std::string & message) 
	{
		sockaddr_in selfAddr;
		selfAddr.sin_family = AF_INET;
		selfAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Envoi � localhost
		selfAddr.sin_port = htons(PORT);  // Utilisation du m�me port que le serveur

		// Envoyer le message
		if (sendto(server_socket, message.c_str(), message.length(), 0, (sockaddr*)&selfAddr, sizeof(selfAddr)) == SOCKET_ERROR) {
			cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
		}
		else {
			GameStatus* gs = new GameStatus();
			gs->fromString(message);
			cout << "Message sent to self: " << message << "\n";
		}
	}
