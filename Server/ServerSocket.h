#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <functional>
#include <vector>
#include <atomic>
#include <thread>

#include "ClientSocket.h"

#pragma comment(lib, "ws2_32.lib")

class ServerSocket {
private:
	int port = -1; // Port to server will listen on
	SOCKET listenSocket; // Socket server opens for clients to connect to
	sockaddr_in serverAddress;
	
public:
	ServerSocket(int port);
	~ServerSocket() { close(); };

	ClientSocket acceptConnection() const; // Accept connections and return when a client connects
	void close();
};