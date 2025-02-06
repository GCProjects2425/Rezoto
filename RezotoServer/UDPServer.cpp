#include "UDPServer.h"
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

    //SendMessageToSelf("const std::string & message");
    while (!exitRequested) {
        //cout << "Waiting for data...\n";
        char message[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int message_len;
        int slen = sizeof(sockaddr_in);
        if ((message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen)) == SOCKET_ERROR) {
            int errorCode = WSAGetLastError();
            //cout << "recvfrom() failed with error code: " << errorCode << "\n";
            if (errorCode == WSAECONNRESET) {
                cout << "Client forcibly closed the connection.\n";
                //}
                continue;  // Continue la boucle au lieu d'exécuter `exit(0)`
            }
            if (errorCode == WSAEWOULDBLOCK)
            {
                continue;
            }
            break;
        }

            // print details of the client/peer and the data received
            cout << "Received packet from " << inet_ntoa(client.sin_addr) << " " << ntohs(client.sin_port) << "\n";
            cout << "Data: " << message << "\n";

            SendMessageToSelf("OK CONNARD");

            /* cout << "Enter response (exit to stop server process): ";
             cin.getline(message, BUFLEN);*/

             //SendMessageToSelf("Ouais ");

             // reply to the client with the same data
             /*if (sendto(server_socket, message, strlen(message), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR) {
                 cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
                 exit(EXIT_FAILURE);
             }*/

             //if(wsase)

            if (strcmp(message, "exit") == 0) {
                cout << "Exiting server...\n";
                exitRequested = true;
                break;
            }
        }

    }


void UDPServer::SendMessageToSelf(const std::string& message)
{
    sockaddr_in selfAddr;
    selfAddr.sin_family = AF_INET;
    selfAddr.sin_addr.s_addr = inet_addr(inet_ntoa(client.sin_addr));  // Envoi à localhost        
    selfAddr.sin_port = htons(client.sin_port);  // Utilisation du même port que le serveur

    // Envoyer le message
    if (sendto(server_socket, message.c_str(), message.length(), 0, (sockaddr*)&selfAddr, sizeof(selfAddr)) == SOCKET_ERROR) {
        std::cout << "sendto() failed with error code: " << WSAGetLastError() << "\n";
    }
    else {
        std::cout << "Message sent to self: " << message << "\n";
    }
}
