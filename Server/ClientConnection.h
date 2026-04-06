#pragma once

#include <WinSock2.h>

class ClientConnection {
private:
	SOCKET socket;

public:
	ClientConnection(SOCKET socket);

	void receive(char* buffer, size_t size);
};