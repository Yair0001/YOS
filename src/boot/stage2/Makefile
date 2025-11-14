# Stage2 Makefile

BUILD_DIR      = $(BUILD)/stage2
INTCONV_OBJ = $(BUILD)/common/intconv.o
SYMBOL_OBJ = $(BUILD)/common/symbol.o
PRINTK_OBJ = $(BUILD)/common/printk.o
COMMON_OBJS := $(PRINTK_OBJ) $(SYMBOL_OBJ) $(INTCONV_OBJ)

STAGE2_BIN     = $(BIN)/stage2.bin
STAGE2_C_SRC   = stage2.c
STAGE2_ASM_SRC = stage2.asm

STAGE2_C_OBJ   = $(BUILD_DIR)/stage2.o
STAGE2_ASM_OBJ = $(BUILD_DIR)/stage2_asm.o
STAGE2_OBJ     = $(BUILD_DIR)/stage2_full.o

all: $(STAGE2_BIN)

$(STAGE2_ASM_OBJ): $(STAGE2_ASM_SRC) | $(BUILD_DIR)
	@echo "ASM: $<"
	$(ASM) -f elf -g $< -o $@

# Compile stage2.c
$(STAGE2_C_OBJ): $(STAGE2_C_SRC) | $(BUILD_DIR)
	@echo "CC: $<"
	$(CC) $(CC_FLAGS) -c $< -o $@

# Combine ASM and C objects into a relocatable object
$(STAGE2_OBJ): $(STAGE2_ASM_OBJ) $(STAGE2_C_OBJ) $(COMMON_OBJS)
	@echo "LD: Relocating stage2 objects"
	$(LD) -g -relocatable $^ -o $@

# Link final binary
$(STAGE2_BIN): $(STAGE2_OBJ)
	@echo "CC: Linking stage2"
	$(CC) $(CC_FLAGS) -T linker.ld -o $@ $<

# Build directory
$(BUILD_DIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(STAGE2_BIN)

.PHONY: all clean
