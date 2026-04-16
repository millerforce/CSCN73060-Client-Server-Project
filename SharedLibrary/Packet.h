#pragma once

#include "UUID.h"

/**
 * @brief Represents a deserialized telemetry data packet.
 *
 * This structure models a packet exchanged between a client and server.
 */
struct Packet {
	/**
	 * @brief Unique identifier of the client.
	 */
	UUID_T clientId;
	/**
	 * @brief Timestamp of the packet (Unix epoch time).
	 */
	int dateTime = 0;
	/**
	 * @brief Fuel value associated with the packet.
	 */
	float fuel = 0.0f;
	/**
	 * @brief CRC value for data integrity.
	 */
	uint16_t crc = 0;

	Packet() = default;

	/**
	 * @brief Constructs a Packet with all fields specified. Used for packets recived.
	 *
	 * @param clientId The client UUID.
	 * @param dateTime The timestamp (Unix epoch time).
	 * @param fuel The fuel value.
	 * @param crc The CRC value for integrity verification.
	 */
	Packet(UUID_T clientId, int dateTime, float fuel, uint16_t crc) : clientId(clientId), dateTime(dateTime), fuel(fuel), crc(crc) {}
	/**
	 * @brief Constructs a Packet without a CRC value. Used for constructing packets to send.
	 *
	 * The CRC field will remain at its default value (0).
	 *
	 * @param clientId The client UUID.
	 * @param dateTime The timestamp (Unix epoch time).
	 * @param fuel The fuel value.
	 */
	Packet(UUID_T clientId, int dateTime, float fuel) : clientId(clientId), dateTime(dateTime), fuel(fuel) {}
};