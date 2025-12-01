# Directories
SRC_DIR = Day1
BUILD_DIR = Day1/build

# Automatically find all .c files in SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Convert source files to output files in BUILD_DIR
# e.g., Day1/Day1Part1.c -> Day1/build/Day1Part1.out
OUTPUTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.out,$(SOURCES))

# Default target: build all
all: $(OUTPUTS)

# Rule to build each .out from .c
$(BUILD_DIR)/%.out: $(SRC_DIR)/%.c | $(BUILD_DIR)
	gcc -o $@ $<

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up
clean:
	rm -f $(BUILD_DIR)/*.out
