#pragma once

#include "Packet.h"

#include <optional>
#include <vector>

class TelemetryWriter {
private:
	std::optional<UUID_T> clientId;
	float totalFuelConsumption; // Tracks the total number of fuel units consumed during the flight
	int consumptionCount; // Counter for the number of times consumption has been added to
	float currentFuelLevel;
	int startTime; // Indicates the dateTime of the first received packet
	int mostRecentTime; // Indicates the dateTime of the last received packet or the current "end" of the flight

	void addConsumption(float fuelLevel); // Takes a new fuel level and performs the subsequent processing
public:
	explicit TelemetryWriter() : clientId(std::nullopt), totalFuelConsumption(0.0f), consumptionCount(0), currentFuelLevel(0.0f), startTime(0), mostRecentTime(0) {}

	void processPacket(const Packet& packet);

	float getTotalConsumption() const;
	float getAverageConsumption() const;

	bool close();// End the current session and write the flights fuel consumption to a file
};