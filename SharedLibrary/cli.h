#pragma once

#include <iostream>
#include <string>
#include <map>

using Args = std::map<std::string, std::string>;

/**
 * @brief Parses command line arguments into a map.
*
* This function takes the command line arguments and parses them into a map
* where the keys are the argument names (e.g., "--port") and the values are
* the corresponding argument values (e.g., "8080").
*
* Example usage:
* --port=5555
*
* @param argc The number of command line arguments.
* @param argv The command line arguments.
* @return A map containing the parsed arguments.
*/
Args parseArgs(int argc, char* argv[]);

/**
 * @brief Retrieves the IP address from parsed arguments.
 *
 * Looks for the "--ip" key in the argument map and returns its value.
 * If the key is not found, the provided default value is returned.
 *
 * @param args The parsed argument map.
 * @param defaultIp The default IP address to return if "--ip" is not present. Defaults to "127.0.0.1".
 * @return std::string The resolved IP address.
 */
std::string getIp(const Args& args, std::string defaultIp = "127.0.0.1");

/**
 * @brief Retrieves the port number from parsed arguments.
 *
 * Looks for the "--port" key in the argument map and converts its value
 * to an integer. If the key is not found, the provided default value is returned.
 *
 * @param args The parsed argument map.
 * @param defaultPort The default port to return if "--port" is not present. Defaults to 23500.
 * @return int The resolved port number.
 *
 * @throws std::invalid_argument If the port value cannot be converted to an integer.
 */
int getPort(const Args& args, int defaultPort = 23500);

/**
 * @brief Retrieves the directory path from parsed arguments.
 *
 * Looks for the "--dir" key in the argument map and returns its value.
 * If the key is not found, the provided default directory is returned.
 *
 * @param args The parsed argument map.
 * @param defaultDir The default directory to return if "--dir" is not present. Defaults to "./data/".
 * @return std::string The resolved directory path.
 */
std::string getDir(const Args& args, std::string defaultDir = "./data/");
