#### KERNEL
#### Gets KERN_BIN & BIN & BUILD & LD & CC from parent Makefile

KERN_ELF = $(BUILD)/kernel.elf
KERN_BUILD = $(BUILD)/kernel.o
KERN_SRC = main.c
KERN_LINKER = linker.ld

LD_FLAGS = -m elf_i386 -T $(KERN_LINKER) -nostdlib

all: $(KERN_BIN)

$(KERN_BIN): 

$(KERN_BIN): $(KERN_ELF)
	i686-elf-objcopy -O binary $< $@

$(KERN_ELF): $(KERN_BUILD)
	$(LD) $(LD_FLAGS) $< -o $@

$(KERN_BUILD): $(KERN_SRC)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -fr $(KERN_BUILD) $(KERN_ELF)
