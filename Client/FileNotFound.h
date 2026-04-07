#pragma once


#include <exception>
#include <string>

class FileNotFoundException : public std::exception {
private:
    std::string message;
public:
    explicit FileNotFoundException(std::string msg) : message(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};


