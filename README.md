# 📡 WSPR Message Generator

## 📖 Overview

**WSPR Message Generator** is a C++ implementation of a **Weak Signal Propagation Reporter (WSPR)** packet generator. This program encodes **callsigns, grid locators, and power levels** into a **162-bit WSPR symbol sequence**, which can be transmitted for propagation testing.

This implementation follows the WSPR protocol, converting user-specified parameters into a symbol sequence that can be used for RF transmission.

## 🚀 Features

- 📡 **Generates WSPR symbol sequences** from callsign, Maidenhead grid locator, and power level.
- 🔤 **Handles callsign formatting** and automatic uppercase conversion.
- 🛠️ **Efficient bitwise operations** for symbol encoding.
- 📝 **C++17 compatible** with memory-safe design.
- 📊 **CLI Output** for debugging and testing.

## 📦 Installation

### 🔧 **Prerequisites**

Ensure you have the following installed:

- `g++` (C++17 or later)
- `Make` (for building)
- `clang-tidy` (for linting, optional)
- `cppcheck` (for static analysis, optional)

### 🏗️ **Build Instructions**

Clone the repository:

```bash
git clone https://github.com/lbussy/WSPR-Message.git
cd WSPR-Message
```

### 🔨 Compile the Core Library

To compile the core WSPR message generator:

```bash
make
```

### 🧪 Run Tests

To compile and run the test program (`main.cpp`):

```bash
make test
./test_wspr
```

### 🧹 Clean Up

To remove compiled files:

```bash
make clean
```

## 🛠️ Usage

After compiling, run the test program:

```bash
./test_wspr
```

Example Output:

```txt
Callsign: AA0NT
Location: EM18
Power: 20 dBm
Generated WSPR symbols:
1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0, ...
```

## 📂 Project Structure

```txt
wspr-message-generator/
│── src/
│   ├── wspr_message.cpp    # Core implementation of WSPR message generation
│   ├── wspr_message.hpp    # Header file for WSPR message class
│── main.cpp                # Test program
│── Makefile                # Build system
│── README.md               # Project documentation
```

## 🔍 Code Quality

### 🧼 Linting

Run `clang-tidy` and `cppcheck` for static analysis:

```bash
make lint
```

### 🧪 Memory Checks

Use `valgrind` for memory leak detection:

```bash
valgrind --leak-check=full ./test_wspr
```

## 🤝 Contributing

I welcome contributions! To contribute:

1. Fork the repository on GitHub.
2. Create a new branch for your feature or bug fix.
3. Commit your changes with meaningful messages.
4. Submit a pull request with a description of your changes.

### 📝 Coding Guidelines

- Follow modern C++ best practices (C++17 and later).
- Ensure memory safety (`delete[]` for allocated memory).
- Use Doxygen-style comments for documentation.
- Run `make lint` before submitting a pull request.

## 📜 License

This project is open-source under the MIT License. See [LICENSE](LICENSE.md) for details.

---

## 🛠️ Maintainers

- Lee C. Bussy (@LBussy)

---

## The WSPR Protocol

The type of radio emission is “F1D”, frequency-shift keying. A message contains a station's callsign, Maidenhead grid locator, and transmitter power in dBm.The WSPR protocol compresses the information in the message into 50 bits (binary digits). These are encoded using a convolutional code with constraint length K = 32 and a rate of r = 1⁄2. The long constraint length makes undetected decoding errors less probable, at the cost that the highly efficient Viterbi algorithm must be replaced by a simple sequential algorithm for the decoding process.
Protocol specification

The standard message is `<callsign>` + `<4 character locator>` + `<dBm transmit power>`; for example “`K1ABC FN20 37`” is a signal from station K1ABC in Maidenhead grid cell “FN20”, sending 37 dBm, or about 5.0 W (legal limit for 630 m). Messages with a compound callsign and/or 6 digit locator use a two-transmission sequence. The first transmission carries compound callsign and power level, or standard callsign, 4 digit locator, and power level; the second transmission carries a hashed callsign, 6 digit locator, and power level. Add-on prefixes can be up to three alphanumeric characters; add-on suffixes can be a single letter or one or two digits.

- Fields of a standard message:
  - 28 bits for callsign,
  - 15 bits for locator,
  - 5 bits for power level,
  - 2 bits for message type,
  - Total: 50 bits.
- Forward error correction (FEC): Non-recursive convolutional code with constraint length K = 32, rate r = 1⁄2.
- Number of binary channel symbols: nsym = (50 + K − 1) × 2 = 162.
- Keying rate is 12000⁄8192 = 1.4648 baud.
- Modulation is continuous phase 4 FSK, with 1.4648 Hz tone separation.
- Occupied bandwidth is about 6 Hz
- Synchronization is via a 162 bit pseudo-random sync vector.
- Each channel symbol conveys one sync bit (LSB) and one data bit (MSB).
- Duration of transmission is 162 × 8192⁄12000 = 110.6 s.
- Transmissions nominally start one second into an even UTC minute: e.g., at hh:00:01, hh:02:01, etc.
- Minimum S/N for reception is around –34 dB on the WSJT scale (2500 Hz reference bandwidth).

### WSPR Links

- [WSPR - This page is a collection of notes and resources related to WSPR transmission and reception.](https://swharden.com/software/FSKview/wspr/)
