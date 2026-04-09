
#include <iostream>

#include "UUID.h"
#include "ClientSocket.h"
#include "file_io.h"
#include "cli.h"

int main(int argc, char* argv[]) {
	Args args = parseArgs(argc, argv);
	int port = getPort(args);
	std::string ipAddress = getIp(args);
	std::string telemDir = getDir(args);

	std::cout << port << std::endl;
	std::cout << ipAddress << std::endl;

	std::string telmFile = getRandomTelemFilename(telemDir);
	std::vector<std::string> telemetryData = readFile(telemDir + telmFile);
	// TODO: parse into vector of packets

	UUID_T clientId;
	std::cout << clientId.toString();

	// psudo code
	//ClientSocket socket = ClientSocket(ipAddress, port);
	//if (socket.isConnected()) {
	//	std::cout << "Connected to Server" << std::endl;
	//}

	//while (telemetryData.size() > 0) {
		//packet = telemetryData.erase(telemetryData.begin());
		//socket.send(packet);
		//std::cout << "Packet Sent" << std::endl;
		//Sleep(1000);
	//}

	//socket.close();

	std::cout << "Closing..." << std::endl;

	return 0;
}
