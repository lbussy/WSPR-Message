/**
 * @file wspr_message.cpp
 * @brief An implementation of a WSPR packet generator.
 *
 * Copyright (C) 2025 Lee C. Bussy (@LBussy). All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "wspr_message.hpp"
#include <iostream> // For: std::cout, std::endl
#include <cctype>   // For: std::isdigit, std::isalpha
#include <cstring>  // For: std::memcpy

/**
 * @brief 162-bit synchronization vector.
 */
const unsigned char sync[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0,
    1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1,
    0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1,
    0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0};

/**
 * @brief Constructs a WSPR message from a callsign, grid location, and power level.
 *
 * @param callsign The callsign to encode. Must be a valid amateur radio callsign.
 * @param location The Maidenhead grid locator (4-character format, e.g., "EM18").
 * @param power The transmission power level in dBm.
 *
 * @note This constructor ensures that the callsign and location are converted to uppercase
 *       before encoding them into the WSPR symbol sequence.
 */
WsprMessage::WsprMessage(const std::string &callsign, const std::string &location, int power)
{
    // Validate input length to prevent out-of-range errors
    if (callsign.empty() || location.length() != 4)
    {
        throw std::invalid_argument("Invalid callsign or location format.");
    }

    // Create modifiable copies for processing
    std::string mod_callsign = callsign;
    std::string mod_location = location;

    // Convert callsign and location to uppercase to comply with WSPR encoding rules
    to_upper(mod_callsign);
    to_upper(mod_location);

    // Generate the WSPR symbols based on the processed callsign, location, and power
    generate_wspr_symbols(mod_callsign, mod_location, power);
}

/**
 * @brief Converts a given string to uppercase.
 *
 * @param str The string to be modified in-place.
 *
 * @note This function modifies the input string directly.
 *       It uses `std::transform` with `::toupper` for efficiency.
 *       Only ASCII characters are guaranteed to be correctly transformed.
 */
void WsprMessage::to_upper(std::string &str)
{
    if (str.empty())
    {
        return; // No processing needed for an empty string
    }

    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::toupper(c); });
}

/**
 * @brief Generates WSPR symbols based on callsign, grid location, and power.
 *
 * @param callsign The amateur radio callsign (up to 6 characters, uppercase).
 * @param location The Maidenhead grid locator (4 characters, uppercase).
 * @param power The transmission power level in dBm (0-60 dBm typical range).
 *
 * @note This function encodes the callsign, grid locator, and power level
 *       into a 162-bit WSPR message and stores the resulting symbols in
 *       the `symbols` array.
 *
 * @throws std::runtime_error If memory allocation for symbols fails.
 */
void WsprMessage::generate_wspr_symbols(const std::string &callsign, const std::string &location, int power)
{
    // Allocate memory for symbols and check for allocation failure
    symbols = new (std::nothrow) unsigned char[MSG_SIZE];
    if (!symbols)
    {
        throw std::runtime_error("Memory allocation failed for WSPR symbols.");
    }

    // Callsign processing - ensure correct structure
    char call[6] = {' ', ' ', ' ', ' ', ' ', ' '}; // Default to padded spaces

    if (callsign.length() >= 2 && std::isdigit(callsign[1]))
    {
        // Numeric second character: shift callsign one position right
        std::copy_n(callsign.begin(), std::min(callsign.length(), size_t(5)), call + 1);
    }
    else if (callsign.length() >= 3 && std::isdigit(callsign[2]))
    {
        // Numeric third character: copy callsign as is
        std::copy_n(callsign.begin(), std::min(callsign.length(), size_t(6)), call);
    }

    // Encode callsign into integer N
    uint32_t N = get_character_value(call[0]) * 36 + get_character_value(call[1]);
    N = N * 10 + get_character_value(call[2]);
    N = N * 27 + get_character_value(call[3]) - 10;
    N = N * 27 + get_character_value(call[4]) - 10;
    N = N * 27 + get_character_value(call[5]) - 10;

    // Encode location and power into integer M
    uint32_t M1 = (179 - 10 * (location[0] - 'A') - (location[2] - '0')) * 180 +
                  (10 * (location[1] - 'A')) + (location[3] - '0');
    uint32_t M = M1 * 128 + power + 64;

    // Initialize symbols array with sync vector
    std::copy(std::begin(sync), std::end(sync), symbols);

    int i;
    uint32_t reg = 0;
    unsigned char reverseAddressIndex = 0;

    // Encode N into symbols using convolutional encoding
    for (i = 27; i >= 0; i--)
    {
        reg <<= 1;
        if (N & ((uint32_t)1 << i))
            reg |= 1;
        symbols[reverse_address(reverseAddressIndex)] += 2 * calculate_parity(reg & 0xf2d05351L);
        symbols[reverse_address(reverseAddressIndex)] += 2 * calculate_parity(reg & 0xe4613c47L);
    }

    // Encode M into symbols
    for (i = 21; i >= 0; i--)
    {
        reg <<= 1;
        if (M & ((uint32_t)1 << i))
            reg |= 1;
        symbols[reverse_address(reverseAddressIndex)] += 2 * calculate_parity(reg & 0xf2d05351L);
        symbols[reverse_address(reverseAddressIndex)] += 2 * calculate_parity(reg & 0xe4613c47L);
    }

    // Final encoding loop for synchronization
    for (i = 30; i >= 0; i--)
    {
        reg <<= 1;
        symbols[reverse_address(reverseAddressIndex)] += 2 * calculate_parity(reg & 0xf2d05351L);
        symbols[reverse_address(reverseAddressIndex)] += 2 * calculate_parity(reg & 0xe4613c47L);
    }
}

/**
 * @brief Converts a character to its corresponding numeric value for WSPR encoding.
 *
 * @param ch The character to convert (digit, letter, or space).
 * @return The numeric value of the character:
 *         - Digits ('0'-'9') return their integer value (0-9).
 *         - Uppercase letters ('A'-'Z') return 10-35.
 *         - A space (' ') returns 36.
 *         - All other characters return 0 (invalid input).
 *
 * @note This function assumes the input character is either a valid alphanumeric
 *       character or a space. Any other input returns 0 as a fallback.
 */
int WsprMessage::get_character_value(char ch)
{
    if (std::isdigit(static_cast<unsigned char>(ch)))
    {
        return ch - '0';
    }
    if (std::isalpha(static_cast<unsigned char>(ch)))
    {
        return 10 + std::toupper(static_cast<unsigned char>(ch)) - 'A';
    }
    if (ch == ' ')
    {
        return 36;
    }

    return 0; // Return 0 for invalid characters
}

/**
 * @brief Reverses the bit order of the address index and ensures it stays within bounds.
 *
 * @param reverseAddressIndex Reference to the current address index, which is incremented.
 * @return The reversed bit address, ensuring it is within the valid WSPR symbol range (0-161).
 *
 * @note This function modifies `reverseAddressIndex` in-place by incrementing it.
 *       If the reversed address is out of range (>161), the function retries until a valid address is found.
 */
unsigned char WsprMessage::reverse_address(unsigned char &reverseAddressIndex)
{
    unsigned char result = reverse_bits(reverseAddressIndex++);

    // Ensure result is within valid range (0-161)
    while (result > 161)
    {
        result = reverse_bits(reverseAddressIndex++);
    }

    return result;
}

/**
 * @brief Reverses the bit order of an 8-bit unsigned integer.
 *
 * @param b The byte (8-bit unsigned char) to reverse.
 * @return The byte with its bits reversed.
 *
 * @note This function performs an in-place bit reversal using bitwise operations.
 *       The algorithm swaps bits in groups of 4, then 2, then 1 to efficiently reverse the byte.
 */
unsigned char WsprMessage::reverse_bits(unsigned char b)
{
    // Swap nibbles (4-bit groups)
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;

    // Swap pairs of bits
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;

    // Swap individual bits
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;

    return b;
}

/**
 * @brief Computes the parity of a 32-bit integer.
 *
 * @param x The 32-bit unsigned integer whose parity is to be calculated.
 * @return 1 if the number of set bits (1s) in `x` is odd, 0 if even.
 *
 * @note This function uses Kernighan’s algorithm to count set bits efficiently.
 *       Each iteration removes the least significant set bit, ensuring O(k) complexity,
 *       where k is the number of bits set in `x`.
 */
int WsprMessage::calculate_parity(uint32_t ch)
{
    int even = 0; // Tracks parity (0 = even, 1 = odd)

    // Iterate through all set bits using Kernighan’s algorithm
    while (ch)
    {
        even = 1 - even;  // Toggle parity
        ch = ch & (ch - 1);  // Remove the lowest set bit
    }

    return even; // Returns 1 for odd parity, 0 for even parity
}

/**
 * @brief Destructor for the WsprMessage class.
 *
 * @note This destructor ensures proper cleanup of dynamically allocated memory for `symbols`.
 *       If `symbols` is already `nullptr`, the delete operation has no effect.
 */
WsprMessage::~WsprMessage()
{
    delete[] symbols; // Deallocates the dynamically allocated symbols array
}
