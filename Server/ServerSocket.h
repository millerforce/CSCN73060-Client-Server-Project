#pragma once

#include <WinSock2.h>

class ServerSocket {
private:
	int port = -1; // Port to server will listen on
	SOCKET socket; // Socket server opens for clients to connect to
	sockaddr_in serverAddress;
public:
	ServerSocket(int port);
	~ServerSocket();


};