.PHONY: all clean stage1 stage2 kernel common os

SRC = $(abspath src/)
BIN = $(abspath bin/)
BUILD = $(abspath build/)
COMMON = $(abspath src/common/)

ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld
CC_FLAGS =  -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -I./src/common
LD_FLAGS  = -m elf_i386 -T linker.ld

export SRC BIN ASM BUILD CC LD CC_FLAGS LD_FLAGS

QEMU = qemu-system-i386
QEMU_FLAGS = -hda

OS_BIN = $(BIN)/os.bin
BOOT_BIN = $(BIN)/boot.bin
KERNEL_BIN = $(BIN)/kernel.bin

all: $(OS_BIN)

common:
	$(MAKE) -C $(SRC)/common

boot: common
	$(MAKE) -C $(SRC)/boot

kernel: common
	$(MAKE) -C $(SRC)/kernel

$(OS_BIN): boot kernel
	@mkdir -p $(BIN)
	cat $(BOOT_BIN) > $@
	dd if=/dev/zero bs=512 count=8 >> $@
	@echo "OS binary created: $(OS_BIN)"

clean:
	$(MAKE) -C $(SRC)/boot clean
	$(MAKE) -C $(SRC)/common clean
	$(MAKE) -C $(SRC)/kernel clean
	rm -fr $(OS_BIN)
	@echo "Clean complete"

run: $(OS_BIN)
	$(QEMU) $(QEMU_FLAGS) $(OS_BIN)

.DEFAULT_GOAL := all
