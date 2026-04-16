#pragma once

#include <vector>

#include "Packet.h"
#include "ClientSocket.h"

/* A handler class used for serializing and deserializing data packets.
Currently provides static methods as there is no necessary reason for
it to store data. This can change if needed. */
class PacketHandler {
private:
	/**
	 * @brief Calculates a simple CRC value for a buffer.
	 *
	 * This CRC is computed by summing the number of set bits (1s) across
	 * the specified number of bytes in the buffer.
	 *
	 * @param buffer The input buffer.
	 * @param length The number of bytes to include in the calculation.
	 * @return uint16_t The computed CRC value.
	 */
	static uint16_t calculateCRC(const SocketBuffer& buffer, size_t length);

	/**
	 * @brief Appends a value's raw bytes into a buffer at a given offset.
	 *
	 * This function copies the memory representation of a value directly
	 * into the buffer.
	 *
	 * @tparam T The type of the value to append.
	 * @param value The value to copy into the buffer.
	 * @param buffer The destination buffer.
	 * @param offset The position in the buffer where the bytes will be written.
	 */
	template<typename T>
	static void appendBytes(const T& value, SocketBuffer& buffer, size_t offset);

	/**
	 * @brief Reads raw bytes from a buffer into a value.
	 *
	 * This function copies bytes from the buffer into the provided variable.
	 *
	 * @tparam T The type of the value to read.
	 * @param value The destination variable.
	 * @param buffer The source buffer.
	 * @param offset The position in the buffer to read from.
	 */
	template<typename T>
	static void readBytes(T& value, const SocketBuffer& buffer, size_t offset);
public:
	/**
	 * @brief Serializes a Packet into a fixed-size buffer.
	 *
	 * The packet fields are written sequentially into the buffer:
	 * - UUID (16 bytes)
	 * - Timestamp (int)
	 * - Fuel (float)
	 * - CRC (uint16_t)
	 *
	 * The CRC is calculated over all preceding bytes and then appended.
	 *
	 * @param packet The packet to serialize. Its CRC field will be updated.
	 * @return SocketBuffer The serialized packet buffer.
	 */
	static SocketBuffer serialize(Packet& packet);
	/**
	 * @brief Deserializes a buffer into a Packet.
	 *
	 * Extracts fields from the buffer in the following order:
	 * - UUID (16 bytes)
	 * - Timestamp (int)
	 * - Fuel (float)
	 * - CRC (uint16_t)
	 *
	 * @param packet The packet object to populate.
	 * @param buffer The input buffer.
	 * @return true If deserialization succd else false
	*/
	static bool deserialize(Packet& packet, const SocketBuffer& buffer);

	/**
	 * @brief Validates a CRC value against buffer contents.
	 *
	 * @param crc The expected CRC value.
	 * @param buffer The buffer to validate.
	 * @param length The number of bytes to include in the CRC calculation.
	 * @return If the CRC matches.
	 */
	static bool checkCRC(uint16_t crc, const SocketBuffer& buffer, size_t length);
};