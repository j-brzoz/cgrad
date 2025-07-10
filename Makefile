CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -O3 -MMD -MP
INCLUDE_DIRS = -Isrc -Isrc/data_structs -Isrc/io -Isrc/ml_structs
LDFLAGS = -lm
SRC_ROOT = src
EXAMPLE_DIR = small_example
BUILD_DIR = build
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/main.out

SRCS = $(wildcard $(SRC_ROOT)/*.c) \
       $(wildcard $(SRC_ROOT)/data_structs/*.c) \
       $(wildcard $(SRC_ROOT)/io/*.c) \
       $(wildcard $(SRC_ROOT)/ml_structs/*.c) \
       $(wildcard $(EXAMPLE_DIR)/*.c)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))
DEPS = $(patsubst %.o,%.d,$(OBJS))
VPATH = $(SRC_ROOT):$(SRC_ROOT)/data_structs:$(SRC_ROOT)/io:$(SRC_ROOT)/ml_structs:$(EXAMPLE_DIR)

all: $(BIN_DIR) $(BUILD_DIR) $(EXECUTABLE)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

-include $(DEPS)