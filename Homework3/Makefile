# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Source file
SRC = src/assignment-sensor.c

# Target binary
TARGET = assignment-sensor

# Default target
all: $(TARGET)

# Build the binary
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up
clean:
	rm -f $(TARGET)
