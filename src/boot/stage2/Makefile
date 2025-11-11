# Gets BIN, BUILD, ASM parameteres from parent Makefile

CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0
ASMFLAGS = -f elf

STAGE2_C = stage2.c
STAGE2_LD   = stage2.ld

STAGE2_BIN  = $(BIN)/stage2.bin
STAGE2_OBJS = $(BUILD)/stage2_asm.o $(BUILD)/stage2.o

all: $(STAGE2_BIN)

$(BUILD)/stage2_asm.o: $(STAGE2_STUB)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD)/stage2.o: $(STAGE2_C)
	$(CC) -c $(CFLAGS) $< -o $@

$(STAGE2_BIN): $(STAGE2_OBJS)
	$(LD) -T $(STAGE2_LD) -o $@ $(STAGE2_OBJS)

clean:
	rm -f $(STAGE2_OBJS) $(STAGE2_BIN)