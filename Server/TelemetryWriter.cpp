
#include "TelemetryWriter.h"
#include "utils.h"

#include <fstream>
#include <string>
#include <filesystem>

void TelemetryWriter::addConsumption(float fuelLevel) {
	// If we have a fuel value from a previous packet then we add the difference between the two
	// to the total consumed fuel
	if (currentFuelLevel > 0) {
		totalFuelConsumption += currentFuelLevel - fuelLevel;
		consumptionCount++; // Increment counter
	}

	// Update current known level to new level
	currentFuelLevel = fuelLevel;
}

void TelemetryWriter::processPacket(const Packet& packet) {
	// If this is the first packet then store clientId
	if (!clientId.has_value()) {
		clientId = packet.clientId;
	}

	// If there is no startTime then store incoming packets as start
	if (startTime == 0) {
		startTime = packet.dateTime;
	}

	// Set most recent time to new packet
	mostRecentTime = packet.dateTime;

	addConsumption(packet.fuel);

	return;
}

float TelemetryWriter::getTotalConsumption() const {
	return totalFuelConsumption;
}

float TelemetryWriter::getAverageConsumption() const {
	return getTotalConsumption() / consumptionCount;
}

bool TelemetryWriter::close() {
	// Early fail if a packet was never received
	if (!clientId.has_value()) return false;

	std::filesystem::create_directories("./flights");

	std::string fileName = "./flights/" + clientId.value().toString() + ".txt";

	std::ofstream flightFile;
	flightFile.open(fileName);

	if (!flightFile.is_open()) return false;

	flightFile << "Flight ID: " << clientId.value().toString() << std::endl;
	flightFile << "Started at: " << epochDateTimeToString(startTime) << std::endl;
	flightFile << "Ended at: " << epochDateTimeToString(mostRecentTime) << std::endl;
	flightFile << "Total fuel consumed: " << getTotalConsumption() << " units" << std::endl;
	flightFile << "Average fuel consumed: " << getAverageConsumption() << " units" << std::endl;

	flightFile.close();

	return true;
}