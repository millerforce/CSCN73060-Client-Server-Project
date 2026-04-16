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

// Our packets are a fixed size
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

	/**
	 * @brief Receives a fixed number of bytes into the provided buffer.
	 *
	 * @param buffer to recive into.
	 * @param size Number of bytes to receive.
	 * @return true If the requested number of bytes was successfully received.
	 * @return false If the connection is closed or the receive operation fails.
	 */
	bool receive(char* buffer, int size);
	/**
	 * @brief Sends data over the socket.
	 *
	 * Sends the contents of the provided fixed-size buffer.
	 *
	 * @param buffer The packet buffer to send.
	 * @return int The number of bytes successfully sent.
	 * @retval -1 If sending fails.
	 */
	int send(const SocketBuffer& buffer) const;

	/**
	 * @brief Closes the socket connection.
	 */
	void close();
	/**
	 * @brief Checks whether the socket is currently connected.
	 */
	bool isConnected() const;

	/**
	 * @brief Sets the socket receive/send timeout.
	 *
	 * @param timeoutSeconds Timeout duration in seconds.
	 * @return bool of if the socket timeout was set successfully
	 */
	bool setSocketTimeout(int timeoutSeconds) const;
};