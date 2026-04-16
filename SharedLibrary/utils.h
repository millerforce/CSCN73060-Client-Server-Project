#pragma once

#include <string>

#include "Packet.h"

/**
 * @brief Converts a formatted date-time string to a Unix epoch timestamp.
 *
 * Parses a date-time string in the format:
 * @code
 * M_D_YYYY HH:MM:SS
 * @endcode
 *
 * Examples:
 * @code
 * "3_3_2023 14:53:22"
 * "12_31_2023 23:59:59"
 * @endcode
 *
 * @param datetime The input date-time string.
 * @return int The corresponding Unix epoch timestamp (seconds since Jan 1, 1970).
 * @retval -1 If parsing fails due to invalid format or values.
 */
int stringToEpochDateTime(const std::string&);

/**
 * @brief Converts a Unix epoch timestamp to a formatted date-time string.
 *
 * Produces a string in the format:
 * @code
 * M_D_YYYY HH:MM:SS
 * @endcode
 *
 * @param epoch The Unix epoch timestamp (seconds since Jan 1, 1970).
 * @return std::string The formatted date-time string.
 * @retval "" If the input epoch value is negative.
 */
std::string epochDateTimeToString(int);

/**
 * @brief Parses a telemetry line into a Packet object.
 *
 * @param clientId The UUID identifying the client that produced the telemetry.
 * @param telem The raw telemetry line as a string.
 * @return Packet The parsed packet containing structured telemetry data.

 */
Packet parseTelemLineToPacket(UUID_T clientId, const std::string& telem);
