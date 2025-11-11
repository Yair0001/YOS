# ================= CONFIG =======================
ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld

FLAGS = -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0
ASMFLAGS = -f elf

BUILD_DIR = ./build
BIN_DIR = ./bin

# Source files
STAGE1_SRC = ./src/boot/stage1/stage1.asm
STAGE2_ASM_SRC = ./src/boot/stage2/stage2.asm
STAGE2_C_SRC = ./src/boot/stage2/stage2.c
LINKER_SCRIPT = ./src/boot/stage2/linker.ld

# Output files
STAGE1_BIN = $(BIN_DIR)/stage1.bin
STAGE2_BIN = $(BIN_DIR)/stage2.bin
OS_IMAGE = $(BIN_DIR)/os.bin

STAGE2_ASM_OBJ = $(BUILD_DIR)/stage2.asm.o
STAGE2_C_OBJ = $(BUILD_DIR)/stage2.o
STAGE2_OBJ = $(BUILD_DIR)/stage2_full.o

# ================= TARGETS ======================

.PHONY: all clean dirs

run: $(OS_IMAGE)
	qemu-system-x86_64 -hda $(OS_IMAGE)

all: dirs $(OS_IMAGE)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# --- Stage 1 bootloader (boot sector) ---
$(STAGE1_BIN): $(STAGE1_SRC)
	$(ASM) -f bin $< -o $@

# --- Stage 2 build (ASM + C) ---
$(STAGE2_ASM_OBJ): $(STAGE2_ASM_SRC)
	$(ASM) $(ASMFLAGS) $< -o $@

$(STAGE2_C_OBJ): $(STAGE2_C_SRC)
	$(CC) $(FLAGS) -c $< -o $@

$(STAGE2_OBJ): $(STAGE2_ASM_OBJ) $(STAGE2_C_OBJ)
	$(LD) -relocatable $^ -o $@

$(STAGE2_BIN): $(STAGE2_OBJ) $(LINKER_SCRIPT)
	$(CC) $(FLAGS) -T $(LINKER_SCRIPT) -o $@ -ffreestanding -nostdlib $(STAGE2_OBJ)

# --- Combine into final image ---
$(OS_IMAGE): $(STAGE1_BIN) $(STAGE2_BIN)
	cat $(STAGE1_BIN) $(STAGE2_BIN) > $@
	dd if=/dev/zero bs=512 count=8 >> $@ 2>/dev/null

# --- Cleanup ---
clean:
	rm -f $(BIN_DIR)/*.bin
	rm -f $(BUILD_DIR)/*.o
