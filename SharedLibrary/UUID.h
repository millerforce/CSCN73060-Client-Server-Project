#pragma once

// Credits:
// - https://github.com/rkg82/uuid-v4
// - https://github.com/mariusbancila/stduuid

#include <array>
#include <string>

#define UUID_SIZE 16

/**
 * @class UUID_T
 * @brief Represents a UUID (Universally Unique Identifier), supporting generation, parsing, and string conversion.
 *
 * This class provides functionality to:
 * - Generate random (version 4) UUIDs
 * - Convert UUIDs to and from byte arrays
 * - Parse UUIDs from strings
 * - Serialize UUIDs to string format
 *
 * Internally, the UUID is stored as a 16-byte array.
 */
class UUID_T {
public:
    /**
     * @brief Generate a new random UUID v4.
     */
    UUID_T() {
        generate();
    }

    /**
     * @brief Create an instance of UUID_T from raw bytes
     */
    explicit UUID_T(const std::array<uint8_t, UUID_SIZE>& bytes) : bytes_arr(bytes) {}

    /**
     * @brief Create an instance of UUID_T from a UUID string
     */
    explicit UUID_T(const std::string& str) {
        fromString(str);
    }

    /**
      * @brief Returns the raw byte representation of the UUID.
      *
      * @return Constant reference to the internal 16-byte array.
      */
    const std::array<uint8_t, UUID_SIZE>& bytes() const;

    /**
     * @brief Converts the UUID to its canonical string representation.
     *
     * The format is: xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
     * (lowercase hexadecimal characters).
     *
     * @return A string representation of the UUID.
     */
    std::string toString() const;

    /**
     * @brief Constructs a UUID from a string.
     *
     * @param str A string representing the UUID (with or without hyphens).
     * @return UUID_T instance parsed from the string.
     *
     * @throws std::invalid_argument If the string is not a valid UUID.
     */
    static UUID_T fromStringStatic(const std::string& str);

    /**
     * @brief Constructs a UUID from a byte array.
     *
     * @param bytes A 16-byte array representing the UUID.
     * @return UUID_T instance initialized with the provided bytes.
     */
    static UUID_T fromBytes(const std::array<uint8_t, UUID_SIZE>& bytes);

private:
    std::array<uint8_t, UUID_SIZE> bytes_arr;

    void generate();

    void fromString(const std::string& str);
};
