#pragma once

#include "Packet.h"

#include <optional>
#include <vector>

class TelemetryWriter {
private:
	/**
	 * @brief Unique identifier of the client associated with this session.
	 */
	std::optional<UUID_T> clientId;
	/**
	 * @brief Tracks the total number of fuel units consumed during the flight
	 */
	float totalFuelConsumption;
	/**
	 * @brief Counter for the number of times consumption has been added to
	 */
	int consumptionCount;
	/**
	 * @brief Most recent fuel level received.
	 */
	float currentFuelLevel;
	/**
	 * @brief Timestamp of the first received packet.
	 */
	int startTime;
	/**
	 * @brief Timestamp of the most recent packet.
	 */
	int mostRecentTime;

	/**
	 * @brief Updates fuel consumption based on a new fuel reading.
	 *
	 * @param fuelLevel The new fuel level reading.
	 */
	void addConsumption(float fuelLevel);
public:
	/**
	 * @brief Default constructor.
	 *
	 * Initializes an empty telemetry session with no client.
	 */
	explicit TelemetryWriter() : clientId(std::nullopt), totalFuelConsumption(0.0f), consumptionCount(0), currentFuelLevel(0.0f), startTime(0), mostRecentTime(0) {}

	/**
	 * @brief Processes an incoming telemetry packet.
	 *
	 * Updates session metadata and fuel consumption based on the packet.
	 * The first packet initializes the client ID and start time.
	 *
	 * @param packet The telemetry packet to process.
	 */
	void processPacket(const Packet& packet);

	/**
	 * @brief Gets the total fuel consumption for the session.
	 *
	 * @return float Total fuel consumed.
	 */
	float getTotalConsumption() const;
	/**
	 * @brief Gets the average fuel consumption per interval.
	 *
	 * The average is calculated as total consumption divided by the number
	 * of consumption updates.
	 */
	float getAverageConsumption() const;

	/**
	 * @brief Finalizes the session and writes results to a file.
	 *
	 * The file is written to the "./flights/" directory using the client UUID as the filename.
	 *
	 * @return true If the file was successfully written.
	 * @return false If no data was available or file operations failed.
	 */
	bool close();
};