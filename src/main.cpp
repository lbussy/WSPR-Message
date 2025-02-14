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
 * @file main.cpp
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
    std::string callsign = "AA0NT";  ///< Amateur radio callsign (uppercase, max 6 characters)
    std::string location = "EM18";   ///< Maidenhead grid locator (4 characters, uppercase)
    int power = 20;                  ///< Transmission power level in dBm

    // Create a WSPR message instance
    WsprMessage message(callsign, location, power);

    // Display input parameters
    std::cout << "Callsign: " << callsign << "\n";
    std::cout << "Location: " << location << "\n";
    std::cout << "Power: " << power << " dBm\n";

    // Output the generated WSPR symbols
    std::cout << "Generated WSPR symbols:\n";

    // Print symbols
    for (int i = 0; i < WsprMessage::size; ++i)
    {
        std::cout << static_cast<int>(message.symbols[i]);
        if (i < WsprMessage::size - 1)
        { 
            std::cout << ","; // Append a comma except for the last element
        }
    }
    std::cout << std::endl;

    return 0; // Indicate successful execution
}
