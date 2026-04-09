#pragma once

// Credits:
// - https://github.com/rkg82/uuid-v4
// - https://github.com/mariusbancila/stduuid

#include <array>
#include <string>

#define UUID_SIZE 16

class UUID_T {
public:
    // Default: generate random UUID_T (v4)
    UUID_T() {
        generate();
    }

    // Construct from raw bytes
    explicit UUID_T(const std::array<uint8_t, UUID_SIZE>& bytes) : bytes_arr(bytes) {}

    // Construct from string
    explicit UUID_T(const std::string& str) {
        fromString(str);
    }

    // Get raw bytes
    const std::array<uint8_t, UUID_SIZE>& bytes() const;

    // Convert to string
    std::string toString() const;

    // Static factory from string
    static UUID_T fromStringStatic(const std::string& str);

    // Static factory from bytes
    static UUID_T fromBytes(const std::array<uint8_t, UUID_SIZE>& bytes);

private:
    std::array<uint8_t, UUID_SIZE> bytes_arr;

    void generate();

    void fromString(const std::string& str);
};
