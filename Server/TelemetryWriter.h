#pragma once

#include "Packet.h"

#include <optional>
#include <vector>

class TelemetryWriter {
private:
	std::optional<UUID_T> clientId;
	std::vector<float> fuelConsumptions;
	float currentFuelLevel;
	int startTime; // Indicates the dateTime of the first received packet
	int mostRecentTime; // Indicates the dateTime of the last received packet or the current "end" of the flight
public:
	explicit TelemetryWriter() : clientId(std::nullopt), fuelConsumptions(0), currentFuelLevel(0.0f), startTime(0), mostRecentTime(0) {}

	void processPacket(const Packet& packet);

	float getTotalConsumption();
	float getAverageConsumption();

	bool close();// End the current session and write the flights fuel consumption to a file
};