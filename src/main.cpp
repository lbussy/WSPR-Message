/**
 * @file main.cpp
 * @brief Test file for the implementation of a WSPR packet generator.
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
#include <iostream>

/**
 * @brief Outputs WSPR symbol values to the console.
 *
 * Iterates over an array of WSPR symbols and prints each symbol as an
 * integer, separated by commas. The output ends with a newline.
 *
 * This function is typically used for debugging or verification of
 * symbol generation logic.
 *
 * @param symbols Pointer to the array of WSPR symbols to be printed.
 * @param count Number of symbols in the array.
 */
void process_symbols(const uint8_t* symbols, std::size_t count)
{
    for (std::size_t i = 0; i < count; ++i)
    {
        {
            std::cout << static_cast<int>(symbols[i]);
            if (i < count - 1)
            {
                std::cout << ","; // Append a comma except for the last element
            }
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Demonstrates the usage of the WsprMessage class to generate WSPR symbols.
 *
 * @return 0 on successful execution.
 *
 * @note This program initializes a WSPR message using a given callsign, grid locator,
 *       and power level, then outputs the generated WSPR symbols to the console.
 */
int main()
{
    // Define callsign, Maidenhead grid location, and power level
    std::string callsign = "AA0NT"; ///< Amateur radio callsign (uppercase, max 6 characters)
    std::string location = "EM18";  ///< Maidenhead grid locator (4 characters, uppercase)
    int power = 20;                 ///< Transmission power level in dBm

    // Create a WSPR message instance
    // WsprMessage wMessage(callsign, location, power);
    WsprMessage wMessage;
    wMessage.set_message_parameters(callsign, location, 20);

    // Display input parameters
    std::cout << "Callsign: " << callsign << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Power: " << power << " dBm" << std::endl;

    process_symbols(wMessage.symbols, WsprMessage::size);

    return 0; // Indicate successful execution
}
