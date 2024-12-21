# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files and executable
SRC = task.c main.c
OBJ = $(SRC:.c=.o)
EXEC = scheduler

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)
