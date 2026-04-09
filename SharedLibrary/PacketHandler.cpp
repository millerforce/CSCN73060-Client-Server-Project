
#include <bit>

#include "PacketHandler.h"

uint16_t PacketHandler::calculateCRC(std::vector<char>& buffer) {

	uint16_t total = 0;

	// Loop through each byte and add the number of 1 bits to the total
	for (unsigned char byte : buffer) {
		total += std::popcount(byte);
	}

	return total;
}

template<typename T>
void PacketHandler::appendBytes(std::vector<char>& buffer, const T& value) {
	// Create a pointer to the values memory
	const char* pointer = reinterpret_cast<const char*>(&value);

	// Append to buffer
	buffer.insert(buffer.end(), pointer, pointer + sizeof(T));
}

SocketBuffer PacketHandler::serialize(Packet& packet) {
	std::vector<char> buffer; // Buffer to populate

	// Copy UUID
	auto& clientIdBuf = packet.clientId.bytes();
	buffer.insert(buffer.end(), clientIdBuf.begin(), clientIdBuf.end());

	// Copy timestamp
	appendBytes(buffer, packet.dateTime);

	// Copy fuel level
	appendBytes(buffer, packet.fuel);

	packet.crc = calculateCRC(buffer);
	appendBytes(buffer, packet.crc);

	return buffer;
}

std::optional<Packet> PacketHandler::deserialize(SocketBuffer& buffer) {
	if (buffer.size() != PACKET_SIZE) return std::nullopt;

	size_t offset = 0;

	// Copy first 16 bytes for clientId
	std::array<uint8_t, UUID_SIZE> uuidBytes;
	std::copy(buffer.begin(), buffer.begin() + UUID_SIZE, uuidBytes.begin());
	offset += UUID_SIZE;
	UUID_T clientId(uuidBytes);

	// Copy next 4 bytes for dateTime
	int dateTime;
	std::memcpy(&dateTime, buffer.data() + offset, sizeof(int));
	offset += sizeof(int);

	// Copy next 4 bytes for fuel
	float fuel;
	std:memcpy(&fuel, buffer.data() + offset, sizeof(float));
	offset += sizeof(float);

	// Copy CRC
	uint16_t crc;
	std::memcpy(&crc, buffer.data() + offset, sizeof(uint16_t));

	// Create a copy of the original buffer without the crc value to compare against
	SocketBuffer compareBuffer(buffer.begin(), buffer.end() - sizeof(uint16_t));

	if (!checkCRC(compareBuffer, crc)) return std::nullopt;

	return Packet(clientId, dateTime, fuel, crc);
}

bool PacketHandler::checkCRC(SocketBuffer& buffer, uint16_t crc) {
	uint16_t bufferCRC = calculateCRC(buffer);// Calculate the number of 1s within the provided buffer

	return bufferCRC == crc;
}