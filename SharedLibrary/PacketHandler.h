#pragma once

#include "Packet.h"
#include "ClientSocket.h"

/* A handler class used for serializing and deserializing data packets.
Currently provides static methods as there is no necessary reason for 
it to store data. This can change if needed. */ 
class PacketHandler {
private:
	static uint16_t calculateCRC(SocketBuffer& buffer); // Take a buffer and return the number of 1s

public:
	SocketBuffer serialize(Packet& packet); // Convert a packet into a buffer
	Packet deserialize(SocketBuffer& buffer); // Convert an incoming buffer into a packet


};