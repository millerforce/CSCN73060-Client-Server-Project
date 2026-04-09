#pragma once

#include <string>

#include "Packet.h"

// Parses a date-time string in the format "M_D_YYYY HH:MM:SS" into a Unix epoch timestamp.
// Example inputs: "3_3_2023 14:53:22", "12_31_2023 23:59:59"
// Returns -1 on parse failure.
int stringToEpochDateTime(const std::string&);

// Converts a Unix epoch timestamp back into "M_D_YYYY HH:MM:SS" format.
// Returns an empty string if the epoch value is negative.
std::string epochDateTimeToString(int);

// Takes in a line of telemetry data from the file and parses it into a packet.
Packet parseTelemLineToPacket(UUID_T clientId, const std::string& telem);
