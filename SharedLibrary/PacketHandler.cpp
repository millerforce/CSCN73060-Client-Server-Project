
#include <bit>

#include "PacketHandler.h"

uint16_t PacketHandler::calculateCRC(const SocketBuffer& buffer, size_t length) {
	uint16_t total = 0;

	// Loop through the desired number of bytes and add the number of 1 bits to the total
	for (size_t i = 0; i < length; ++i) {
		total += std::popcount(static_cast<unsigned char>(buffer[i]));
	}

	return total;
}

template<typename T>
void PacketHandler::appendBytes(const T& value, SocketBuffer& buffer, size_t offset) {
	// Create a pointer to the values memory
	const char* pointer = reinterpret_cast<const char*>(&value);

	// Append to buffer
	std::memcpy(buffer.data() + offset, pointer, sizeof(T));
}

template<typename T>
void PacketHandler::readBytes(T& value, const SocketBuffer& buffer, size_t offset) {
	std::memcpy(&value, buffer.data() + offset, sizeof(T));
}

SocketBuffer PacketHandler::serialize(Packet& packet) {
	SocketBuffer buffer{}; // Buffer to populate
	size_t offset = 0;

	// Copy UUID
	auto& clientIdBuf = packet.clientId.bytes();
	std::memcpy(buffer.data() + offset, clientIdBuf.data(), clientIdBuf.size());
	offset += clientIdBuf.size();

	// Copy timestamp
	appendBytes(packet.dateTime, buffer, offset);
	offset += sizeof(packet.dateTime);

	// Copy fuel level
	appendBytes(packet.fuel, buffer, offset);
	offset += sizeof(packet.fuel);

	packet.crc = calculateCRC(buffer, offset);
	appendBytes(packet.crc, buffer, offset);

	return buffer;
}

bool PacketHandler::deserialize(Packet& packet, const SocketBuffer& buffer) {
	if (buffer.size() != PACKET_SIZE) return false;

	size_t offset = 0;

	// Copy first 16 bytes for clientId
	std::array<uint8_t, UUID_SIZE> uuidBytes{};
	std::memcpy(uuidBytes.data(), buffer.data() + offset, UUID_SIZE);
	offset += UUID_SIZE;

	UUID_T clientId(uuidBytes);

	// Copy next 4 bytes for dateTime
	int dateTime = 0;
	readBytes(dateTime, buffer, offset);
	offset += sizeof(int);

	// Copy next 4 bytes for fuel
	float fuel = 0.0f;
	readBytes(fuel, buffer, offset);
	offset += sizeof(float);

	// Copy CRC
	uint16_t crc = 0;
	readBytes(crc, buffer, offset);

	if (!checkCRC(crc, buffer, offset)) return false;

	packet = Packet(clientId, dateTime, fuel, crc);

	return true;
}

bool PacketHandler::checkCRC(uint16_t crc, const SocketBuffer& buffer, size_t length) {
	uint16_t bufferCRC = calculateCRC(buffer, length);// Calculate the number of 1s within the provided buffer

	return bufferCRC == crc;
}