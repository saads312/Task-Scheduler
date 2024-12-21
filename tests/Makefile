# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I../src

# Source and test files
SRC_FILES = ../src/task.c
TEST_FILE = test_queue.c

# Output binary
TEST_BIN = test_queue

# Default target
all: $(TEST_BIN)

# Build the test binary
$(TEST_BIN): $(SRC_FILES) $(TEST_FILE)
	$(CC) $(CFLAGS) -o $@ $^

# Run the tests
test: $(TEST_BIN)
	./$(TEST_BIN)

# Clean build artifacts
clean:
	rm -f $(TEST_BIN)

# Phony targets
.PHONY: all test clean
