
#include <iostream>

#include "UUID.h"
#include "file_io.h"

int main(void) {

	std::string telmFile = getRandomTelemFilename();

	std::vector<std::string> telemetryData = readFile("./data/" + telmFile);
	UUID clientId;

	return 0;
}
