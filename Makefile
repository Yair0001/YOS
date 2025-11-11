ASM = nasm
ASMFLAGS= -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

CC = i686-elf-gcc
CFLAGS = -ffreestanding -m16 -O0 -Wall -I./src

LD = i686-elf-ld
LDFLAGS = -T

BUILD = build
BIN = bin
BOOT = src/bootloader

export ASM ASMFLAGS CC CFLAGS LD LDFLAGS


#### BOOTLOADER
BOOT = src/bootloader
STAGE1_DIR = $(BOOT)/stage1
STAGE2_DIR = $(BOOT)/stage2

STAGE1_BIN = $(BIN)/stage1.bin
STAGE2_BIN = $(BIN)/stage2.bin


run: all
	qemu-system-x86_64 -hda $(BIN)/os.bin

all: $(BIN)/os.bin

$(BIN)/os.bin: ($STAGE1_BIN) $(STAGE2_BIN)
	cp $< $@
	cat $(word 2, $^) >> $@
	dd if=/dev/zero bs=512 count=8 >> ./bin/os.bin

clean:
	rm -f $(BIN)/os.bin

