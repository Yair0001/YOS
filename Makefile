
.PHONY: all clean stage1 kernel common run debug verify
.DEFAULT_GOAL := all

SRC    = $(abspath src/)
BIN    = $(abspath bin/)
BUILD  = $(abspath build/)
COMMON = $(abspath src/common/)

BOOT_DIR   = $(SRC)/boot
KERNEL_DIR = $(SRC)/kernel

ASM = nasm
CC  = i686-elf-gcc
LD  = i686-elf-ld

CC_FLAGS = -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -I$(SRC)
LD_FLAGS = -m elf_i386

export SRC BIN ASM BUILD CC LD CC_FLAGS LD_FLAGS


QEMU       = qemu-system-i386
QEMU_FLAGS = -drive file=
QEMU_FMT   = ,format=raw


OS_BIN     = $(BIN)/os.bin
STAGE1_BIN = $(BIN)/stage1.bin
KERNEL_BIN = $(BIN)/kernel.bin

KERNEL_SECTORS_FILE = $(BUILD)/kernel_sectors.txt

get_file_size = $(shell stat -f%z "$(1)" 2>/dev/null || stat -c%s "$(1)" 2>/dev/null)

calc_sectors = $(shell echo $$((($(call get_file_size,$(1)) + 511) / 512)))


all: $(OS_BIN)

common:
	@echo "=== Building common utilities ==="
	$(MAKE) -C $(COMMON)

kernel: common
	@echo "=== Building kernel ==="
	$(MAKE) -C $(KERNEL_DIR)

$(KERNEL_SECTORS_FILE): kernel
	@mkdir -p $(BUILD)
	@KERNEL_SIZE=$(call get_file_size,$(KERNEL_BIN)); \
	KERNEL_SECTORS=$(call calc_sectors,$(KERNEL_BIN)); \
	echo "Kernel size: $${KERNEL_SIZE} bytes ($$KERNEL_SECTORS sectors)"; \
	echo $$KERNEL_SECTORS > $@

stage1: $(KERNEL_SECTORS_FILE)
	@echo "=== Building stage1 bootloader ==="
	$(MAKE) -C $(BOOT_DIR)

$(OS_BIN): stage1 kernel
	@mkdir -p $(BIN)
	@echo "=== Assembling OS image ==="
	cat $(STAGE1_BIN) $(KERNEL_BIN) > $@
	@echo "Total OS size: $(call get_file_size,$@) bytes"
	@echo "OS binary created: $(OS_BIN)"


clean:
	@echo "=== Cleaning build artifacts ==="
	$(MAKE) -C $(BOOT_DIR) clean
	$(MAKE) -C $(COMMON) clean
	$(MAKE) -C $(KERNEL_DIR) clean
	rm -rf $(BIN) $(BUILD)
	@echo "Clean complete"

run: $(OS_BIN)
	@echo "=== Running OS in QEMU ==="
	$(QEMU) $(QEMU_FLAGS)$(OS_BIN)$(QEMU_FMT) -boot c

debug: $(OS_BIN)
	@echo "=== Running OS in QEMU (debug mode) ==="
	$(QEMU) $(QEMU_FLAGS)$(OS_BIN)$(QEMU_FMT) -boot c -d int -no-reboot

verify: $(OS_BIN)
	@echo "=== Verifying OS Image ==="
	@echo "Total size: $(call get_file_size,$(OS_BIN)) bytes"
	@echo ""
	@echo "First 512 bytes (stage1 bootloader):"
	@hexdump -C $(OS_BIN) | head -n 33
	@echo ""
	@echo "Boot signature at offset 510-511 (should be 55 AA):"
	@dd if=$(OS_BIN) bs=1 skip=510 count=2 2>/dev/null | hexdump -C
	@echo ""
	@if [ -f "$(KERNEL_SECTORS_FILE)" ]; then \
		echo "Kernel sectors: $$(cat $(KERNEL_SECTORS_FILE))"; \
	fi
