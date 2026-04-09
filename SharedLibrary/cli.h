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

std::string getIp(const Args& args, std::string defaultIp = "127.0.0.1");

// Returns the value of the specified argument from the map, or a default value if not found.
int getPort(const Args& args, int defaultPort = 23500);

std::string getDir(const Args& args, std::string defaultDir = "./data/");
