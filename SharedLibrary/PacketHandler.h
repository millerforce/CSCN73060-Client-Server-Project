#pragma once

#include <vector>

#include "Packet.h"
#include "ClientSocket.h"

/* A handler class used for serializing and deserializing data packets.
Currently provides static methods as there is no necessary reason for 
it to store data. This can change if needed. */ 
class PacketHandler {
private:
	static uint16_t calculateCRC(const SocketBuffer& buffer, size_t length); // Take a buffer and return the number of 1s

	template<typename T>
	static void appendBytes(const T& value, SocketBuffer& buffer, size_t offset); // Used to append a provide values binary representation into a vector of bytes
	
	template<typename T>
	static void readBytes(T& value, const SocketBuffer& buffer, size_t offset);
public:
	static SocketBuffer serialize(Packet& packet); // Convert a packet into a buffer
	static bool deserialize(Packet& packet, const SocketBuffer& buffer); // Convert an incoming buffer into a packet

	static bool checkCRC(uint16_t crc, const SocketBuffer& buffer, size_t length);
};