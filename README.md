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

**Example Output**

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
