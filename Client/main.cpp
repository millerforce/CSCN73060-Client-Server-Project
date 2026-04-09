
#include <iostream>

#include "UUID.h"
#include "file_io.h"
#include "cli.h"
#include "utils.h"
#include "Packet.h"
#include "PacketHandler.h"

int main(int argc, char* argv[]) {
	Args args = parseArgs(argc, argv);
	int port = getPort(args);
	std::string ipAddress = getIp(args);
	std::string telemDir = getDir(args);

	std::cout << port << std::endl;
	std::cout << ipAddress << std::endl;

	std::string telmFile = getRandomTelemFilename(telemDir);
	std::vector<std::string> telemetryData = readFile(telemDir + telmFile);

	UUID_T clientId;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed: " << WSAGetLastError() << "\n";
		return 1;
	}

	ClientSocket socket(ipAddress, port);
	if (socket.isConnected()) {
		std::cout << "Connected to Server" << std::endl;
	}

	while (telemetryData.size() > 0) {
		if (telemetryData[0].empty()) {
			telemetryData.erase(telemetryData.begin());
			continue;
		}
		Packet packet = parseTelemLineToPacket(clientId, telemetryData[0]);
		telemetryData.erase(telemetryData.begin());
		socket.send(PacketHandler::serialize(packet));
		std::cout << "Packet Sent: " << packet.clientId.toString() << " " << packet.fuel << " " << packet.dateTime << std::endl;
		Sleep(1000);
	}

	socket.close();
	WSACleanup();

	std::cout << "Closing..." << std::endl;

	return 0;
}
