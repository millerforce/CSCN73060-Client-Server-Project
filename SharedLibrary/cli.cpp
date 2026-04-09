
#include "cli.h"

Args parseArgs(int argc, char* argv[]) {
    Args args;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.rfind("--", 0) == 0) {
            size_t equalPosition = arg.find('=');
            if (equalPosition != std::string::npos) {
                std::string key = arg.substr(2, equalPosition - 2);
                std::string value = arg.substr(equalPosition + 1);
                args[key] = value;
            }
            else {
                std::cerr << "Warning: Invalid argument format: " << arg << std::endl;
            }
        }
        else {
            std::cerr << "Warning: Ignoring unrecognized argument: " << arg << std::endl;
        }
    }

    return args;
}

int getPort(const Args& args, int defaultPort) {
    auto argsIterator = args.find("port");
    if (argsIterator != args.end()) {
        try {
            return std::stoi(argsIterator->second);
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Invalid port number: " << argsIterator->second << std::endl;
        }
    }
    return defaultPort;
}

std::string getIp(const Args& args, std::string defaultIp) {
    auto argsIterator = args.find("ip");
    if (argsIterator != args.end()) {
        return argsIterator->second;

    }
    return defaultIp;
}

std::string getDir(const Args& args, std::string defaultDir) {
    auto argsIterator = args.find("dir");
    if (argsIterator != args.end()) {
        return argsIterator->second;

    }
    return defaultDir;
}