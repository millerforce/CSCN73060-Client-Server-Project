#pragma once

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <optional>
#include <string>
#include <syncstream>
#include <iostream>
#include <array>

constexpr size_t PACKET_SIZE = 26;

// Alias for a byte buffer to simplify functions
using SocketBuffer = std::array<char, PACKET_SIZE>;

// Abstraction for a TCP socket with methods for sending and receiving data
class ClientSocket {
private:
	SOCKET connectionSocket;
	bool connected;

public:
	ClientSocket(SOCKET socket) : connectionSocket(socket), connected(true) {} // Create object with existing socket
	ClientSocket(const std::string& IPAddr, int port); // Create object with new socket

	bool receive(char* buffer, int size); // Receive provided number of bytes into a provided buffer
	int send(const SocketBuffer& buffer) const; // Send data from provided buffer

	void close(); // Close the contained socket
	bool isConnected() const; // Get whether the socket is currently connected or not

	bool setSocketTimeout(int timeoutSeconds) const;
};