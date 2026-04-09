
#include <iostream>
#include <fstream>
#include <sstream>

#include <filesystem>
#include <stdexcept>
#include <random>

#include "file_io.h"
#include "FileNotFound.h"

using namespace std;

std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileNotFoundException("Failed to find the file");
    }

    std::string line;

    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    return lines;
}

std::string getRandomTelemFilename(const std::string& directory) {
    namespace fs = std::filesystem;

    std::vector<std::string> txtFiles;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path().filename().string());
        }
    }

    if (txtFiles.empty()) {
        throw std::runtime_error("No .txt files found in " + directory);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, txtFiles.size() - 1);

    return txtFiles[dist(gen)];
}
