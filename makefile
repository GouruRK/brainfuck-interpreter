# Compiler
CC=gcc

# Directories
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
BIN_DIR=bin
INCLUDE=-I$(INC_DIR)

# Flags
CFLAGS=-Wall -std=c17 -Wextra

# Output
EXEC=$(BIN_DIR)/brainfuck

# Sources
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir --parents $(BIN_DIR)
	$(CC) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)
