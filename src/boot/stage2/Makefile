# Gets BIN, BUILD, ASM parameteres from parent Makefile

CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0
ASMFLAGS = -f elf

STAGE2_C = stage2.c
STAGE2_LD = linker.ld

STAGE2_ASM_SRC = stage2.asm
STAGE2_ASM_OBJ = $(BUILD)/stage2.asm.o
STAGE2_C_OBJ = $(BUILD)/stage2.o
STAGE2_OBJ = $(BUILD)/stage2_full.o

STAGE2_BIN  = $(BIN)/stage2.bin

all: $(STAGE2_BIN)

$(STAGE2_ASM_OBJ): $(STAGE2_ASM_SRC)
	$(ASM) $(ASMFLAGS) $< -o $@

$(STAGE2_C_OBJ): $(STAGE2_C)
	$(CC) -c $(CFLAGS) $< -o $@ 

$(STAGE2_BIN): $(STAGE2_OBJ)
	$(CC) $(CFLAGS) -T $(STAGE2_LD) -o $@ -ffreestanding -nostdlib $<

$(STAGE2_OBJ): $(STAGE2_ASM_OBJ) $(STAGE2_C_OBJ)
	$(LD) -relocatable $^ -o $@

clean:
	rm -f $(STAGE2_OBJ) $(STAGE2_BIN) $(STAGE2_ASM_OBJ) $(STAGE2_C_OBJ)