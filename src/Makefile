# -----------------------------------------------------------------------------
# MIT License
# 
# Copyright (c) 2025 Lee C. Bussy (@lbussy)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# provided to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# -----------------------------------------------------------------------------

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
TESTFLAGS := -g -O0

# Source files
SRC := wspr_message.cpp
OBJ := $(SRC:.cpp=.o)
TEST_SRC := main.cpp
TEST_OBJ := $(TEST_SRC:.cpp=.o)

# Output library and test binary
LIB := libwspr_message.a
TEST_BIN := test_wspr

# Default target: only compile object files
all: $(OBJ)

# Build the static library
$(LIB): $(OBJ)
	ar rcs $@ $^

# Build the test binary
test: $(TEST_BIN)

$(TEST_BIN): $(OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(TESTFLAGS) -o $@ $^
	./$(TEST_BIN)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Static analysis and linting
lint:
	@echo "Running clang-tidy..."
	@clang-tidy $(SRC) $(TEST_SRC) -- -std=c++17 $(CXXFLAGS) || true
	@echo "Running cppcheck..."
	@cppcheck --enable=all --inconclusive --quiet --std=c++17 $(SRC) $(TEST_SRC) || true

# Run memory leak check with Valgrind
valgrind: $(TEST_BIN)
	@echo "Running Valgrind memory check..."
	valgrind --suppressions=/dev/null --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_BIN)

# Clean up object files and binaries
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(LIB) $(TEST_BIN) *.o *.d *.a

# Display help message
help:
	@echo "Available Makefile targets:"
	@echo "  all        - Compile the core WSPR message generator"
	@echo "  test       - Build and run the test program (main.cpp)"
	@echo "  lint       - Run static analysis (clang-tidy & cppcheck)"
	@echo "  valgrind   - Run memory leak checks with Valgrind"
	@echo "  clean      - Remove compiled files and binaries"
	@echo "  help       - Show this help message"

.PHONY: all test lint valgrind clean help
