
#include <iostream>

#include "UUID.h"
//#include "ClientSocket.h"
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
	UUID_T clientId;

	std::cout << clientId.toString();

	//ClientSocket socket = ClientSocket("127.0.0.1", 5555);





	//socket.close();

	return 0;
}
