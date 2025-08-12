CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -O3
INCLUDE_DIRS = -Isrc -Isrc/data_structs -Isrc/io -Isrc/ml_structs
LDFLAGS = -lm
SRC_ROOT = src
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/main.out

CORE_SRCS = $(wildcard $(SRC_ROOT)/*.c) \
            $(wildcard $(SRC_ROOT)/data_structs/*.c) \
            $(wildcard $(SRC_ROOT)/io/*.c) \
            $(wildcard $(SRC_ROOT)/ml_structs/*.c)

.PHONY: small big clean

small: $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(CORE_SRCS) small_example/main.c $(LDFLAGS) -o $(EXECUTABLE)

big: $(BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(CORE_SRCS) big_example/main.c $(LDFLAGS) -o $(EXECUTABLE)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(BIN_DIR)