
BUILD_DIR = $(BUILD)/common

C_SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS))

all: $(OBJS)

$(BUILD_DIR)/%.o: %.c %.h | $(BUILD_DIR)
	@echo "CC: $<"
	$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
