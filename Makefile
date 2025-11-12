BIN = $(abspath bin/)
BUILD = $(abspath build/)
ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld
CC_FLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

export BIN ASM BUILD CC LD CC_FLAGS

QEMU = qemu-system-i386
QEMU_FLAGS = -hda

BOOT_DIR = src/boot
BOOT_BIN = $(BIN)/boot.bin

KERN_DIR = src/kernel
KERN_BIN = $(BIN)/kern.bin

OS_BIN = $(BIN)/os.bin

debug:
	$(QEMU) $(QEMU_FLAGS) $(OS_BIN) -d guest_errors,int

run: all
	$(QEMU) $(QEMU_FLAGS) $(OS_BIN)

all: $(OS_BIN)

$(OS_BIN): $(BOOT_BIN) $(KERN_BIN)
	cp $< $@
	cat $(word 2, $^) >> $@
	dd if=/dev/zero bs=512 count=8 >> $@


$(BOOT_BIN):
	$(MAKE) -C $(BOOT_DIR) BOOT_BIN=$(BOOT_BIN)

$(KERN_BIN):
	$(MAKE) -C $(KERN_DIR) KERN_BIN=$(KERN_BIN)
	
clean:
	$(MAKE) -C $(BOOT_DIR) clean BOOT_BIN=$(BOOT_BIN)
	$(MAKE) -C $(KERN_DIR) clean KERN_BIN=$(KERN_BIN)

.PHONY: clean all