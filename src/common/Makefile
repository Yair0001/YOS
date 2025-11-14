
C_SRC = intconv.c printk.c symbol.c

BUILD_DIR = $(BUILD)/common

INTCONV_OBJ = $(BUILD_DIR)/intconv.o
SYMBOL_OBJ = $(BUILD_DIR)/symbol.o
PRINTK_OBJ = $(BUILD_DIR)/printk.o

OBJS = $(PRINTK_OBJ) $(SYMBOL_OBJ) $(INTCONV_OBJ)

all: $(OBJS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(PRINTK_OBJ): intconv.c intconv.h | $(BUILD_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(SYMBOL_OBJ): printk.c printk.h | $(BUILD_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(INTCONV_OBJ): symbol.c symbol.h | $(BUILD_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

.PHONY: all clean