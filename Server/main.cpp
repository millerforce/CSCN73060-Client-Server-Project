
#include <iostream>

#include "ServerController.h"
#include "PacketHandler.h"
#include "utils.h"
#include "TelemetryWriter.h"

constexpr int CLIENT_TIMEOUT = 15;

static void clientFunc(ClientSocket& socket) {
	TelemetryWriter writer;

	socket.setSocketTimeout(CLIENT_TIMEOUT);

	SocketBuffer buffer{};
	Packet packet;

	while (socket.isConnected()) {
		if (!socket.receive(buffer.data(), PACKET_SIZE)) {
			std::osyncstream(std::cerr) << "Failed to receive from client, WSA Error: " << WSAGetLastError() << std::endl;
			break;
		}

		#ifdef _DEBUG
			std::osyncstream(std::cout) << "Packet received" << std::endl;
		#endif // DEBUG

		if (!PacketHandler::deserialize(packet, buffer)) {
			std::osyncstream(std::cerr) << "Failed to parse packet" << std::endl;
			break;
		}

		writer.processPacket(packet);
	}

	bool result = writer.close();

	if (result) std::osyncstream(std::cout) << "Client flight ended successfully" << std::endl;
	else std::osyncstream(std::cout) << "Client flight ended unsuccessfully" << std::endl;

	socket.close(); // Cleanup socket

	return;
}

int main(void) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Error occured when starting Winsock" << std::endl;
	}

	int port = 9000;

	ServerSocket socket(port);

	ClientHandler handler = clientFunc;

	ServerController controller(socket, handler);

	std::cout << "Starting server on port: " << port << std::endl;
	controller.start();
	std::cout << "Server started" << std::endl;

	controller.getAcceptThread().join();

	WSACleanup();
}