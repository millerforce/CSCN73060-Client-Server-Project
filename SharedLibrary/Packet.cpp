
#include "Packet.h"

bool Packet::validate() const {
	// CRC not considered as it is set at serialization
	return clientId.toString().length() == 16 && dateTime > 0 && fuel >= 0;
}