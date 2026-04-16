#pragma once

#include <vector>
#include <string>

/**
 * @brief Reads all lines from a file into a vector of strings.
 *
 * @param filename The path to the file to read.
 * @return std::vector<std::string> A vector containing all lines from the file.
 *
 * @throws FileNotFoundException If the file cannot be opened.
 */
std::vector<std::string> readFile(const std::string& filename);

/**
 * @brief Selects a random telemetry file from a directory.
 *
 * Scans the specified directory for files with a ".txt" extension and randomly selects one of them.
 *
 * @param directory The directory to search for telemetry files.
 * @return std::string The filename (not full path) of a randomly selected file.
 */
std::string getRandomTelemFilename(const std::string& directory);
