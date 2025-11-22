# Kernel Makefile

BUILD_DIR = $(BUILD)/kernel
KERNEL_BIN = $(BIN)/kernel.bin
LINKER_SCRIPT = linker.ld

ASM_SRCS = $(wildcard *.asm) $(wildcard */*.asm)
C_SRCS = $(wildcard *.c) $(wildcard */*.c)

ASM_OBJS = $(patsubst %.asm,$(BUILD_DIR)/%_asm.o,$(ASM_SRCS))
C_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SRCS))

KERNEL_OBJS = $(ASM_OBJS) $(C_OBJS)

COMMON_OBJS = $(wildcard $(BUILD)/common/*.o)

KERNEL_FULL_OBJ = $(BUILD_DIR)/kernel_full.o

all: $(KERNEL_BIN)

$(BUILD_DIR)/%_asm.o: %.asm
	@mkdir -p $(dir $@)
	@echo "ASM: $<"
	$(ASM) -f elf -g $< -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "CC: $<"
	$(CC) $(CC_FLAGS) -c $< -o $@

$(KERNEL_FULL_OBJ): $(KERNEL_OBJS) $(COMMON_OBJS)
	@echo "LD: Relocating kernel objects"
	$(LD) -g -relocatable $^ -o $@

$(KERNEL_BIN): $(KERNEL_FULL_OBJ) $(LINKER_SCRIPT)
	@echo "LD: Linking kernel binary"
	@mkdir -p $(BIN)
	$(CC) $(CC_FLAGS) -T $(LINKER_SCRIPT) -o $@ $(KERNEL_FULL_OBJ)

clean:
	rm -rf $(BUILD_DIR) $(KERNEL_BIN)

.PHONY: all clean
