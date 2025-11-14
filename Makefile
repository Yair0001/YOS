# ================= CONFIG =======================
ASM              = nasm
CC               = i686-elf-gcc
LD               = i686-elf-ld

CFLAGS           = -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -I./src/common
ASMFLAGS         = -f elf -g

BUILD_DIR        = build
BIN_DIR          = bin

STAGE1_SRC       = src/boot/stage1/stage1.asm
STAGE2_ASM_SRC   = src/boot/stage2/stage2.asm
STAGE2_C_SRC     = src/boot/stage2/stage2.c
LINKER_SCRIPT    = src/boot/linker.ld

STAGE1_BIN       = $(BIN_DIR)/stage1.bin
STAGE2_BIN       = $(BIN_DIR)/stage2.bin
OS_IMAGE         = $(BIN_DIR)/os.bin

STAGE2_ASM_OBJ   = $(BUILD_DIR)/stage2.asm.o
STAGE2_C_OBJ     = $(BUILD_DIR)/stage2.o
STAGE2_OBJ       = $(BUILD_DIR)/stage2_full.o

# Auto-include all src/common/*.c
COMMON_SRCS      := $(wildcard src/common/*.c)
COMMON_OBJS      := $(patsubst src/common/%.c, $(BUILD_DIR)/%.o, $(COMMON_SRCS))

# Colors
OK   = \033[32m[OK]\033[0m
CCL  = \033[36m[CC]\033[0m
ASMCL= \033[35m[ASM]\033[0m
LDCL = \033[33m[LD]\033[0m

# ================= TARGETS ======================

.PHONY: all clean run dirs

all: dirs $(OS_IMAGE)

run: $(OS_IMAGE)
	qemu-system-x86_64 -hda $(OS_IMAGE)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# -------- COMMON C FILES (auto detected) --------
$(BUILD_DIR)/%.o: src/common/%.c
	@echo "$(CCL) $<"
	$(CC) $(CFLAGS) -c $< -o $@

# -------- STAGE 1 BOOTLOADER --------
$(STAGE1_BIN): $(STAGE1_SRC)
	@echo "$(ASMCL) $<"
	$(ASM) -f bin $< -o $@

# -------- STAGE 2 OBJECTS --------
$(STAGE2_ASM_OBJ): $(STAGE2_ASM_SRC)
	@echo "$(ASMCL) $<"
	$(ASM) $(ASMFLAGS) $< -o $@

$(STAGE2_C_OBJ): $(STAGE2_C_SRC)
	@echo "$(CCL) $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(STAGE2_OBJ): $(STAGE2_ASM_OBJ) $(STAGE2_C_OBJ) $(COMMON_OBJS)
	@echo "$(LDCL) Relocating stage2 objects"
	$(LD) -g -relocatable $^ -o $@

$(STAGE2_BIN): $(STAGE2_OBJ) $(LINKER_SCRIPT)
	@echo "$(LDCL) Linking stage2"
	$(CC) $(CFLAGS) -T $(LINKER_SCRIPT) -o $@ $(STAGE2_OBJ)

# -------- FINAL DISK IMAGE --------
$(OS_IMAGE): $(STAGE1_BIN) $(STAGE2_BIN)
	@echo "Building final OS image"
	cat $^ > $@
	dd if=/dev/zero bs=512 count=8 >> $@ 2>/dev/null

# -------- CLEAN --------
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)
