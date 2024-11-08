# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR = .
OBJ_DIR = obj

# List of source files
SRCS = $(SRC_DIR)/cpu.cpp $(SRC_DIR)/memory.cpp $(SRC_DIR)/emulator.cpp $(SRC_DIR)/jsonTesting.hpp $(SRC_DIR)/main.cpp 
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output binary
TARGET = gameboy-emulator

# Default target
all: $(TARGET)

# Create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build the target executable
$(TARGET): $(OBJ_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and the target
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Phony targets
.PHONY: all clean

