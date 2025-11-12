BIN = $(abspath bin/)
BUILD = $(abspath build/)
ASM = nasm
export BIN ASM BUILD

QEMU = qemu-system-x86_64
QEMU_FLAGS = -hda
BOOT_DIR = src/boot
BOOT_BIN = $(BIN)/boot.bin

run: all
	$(QEMU) $(QEMU_FLAGS) $(BOOT_BIN)

all: $(BOOT_BIN)

$(BOOT_BIN):
	$(MAKE) -C $(BOOT_DIR) BOOT_BIN=$(BOOT_BIN)
clean:
	$(MAKE) -C $(BOOT_DIR) clean BOOT_BIN=$(BOOT_BIN)

.PHONY: clean all