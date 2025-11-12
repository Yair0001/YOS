# Stage2 Makefile
# Uses ASM, BUILD, BIN, CC, LD, CC_FLAGS, LD_FLAGS from parent Makefile

ASM_FLAGS = -g -f elf32

STAGE2_BIN = $(BIN)/stage2.bin
STAGE2_ELF = $(BUILD)/stage2.elf
STAGE2_SRC = stage2.c

DISK_C_SRC = disk/disk.c
DISK_ASM_SRC = disk/disk.asm

DISK_C_OBJ   = $(BUILD)/disk/disk_c.o
DISK_ASM_OBJ = $(BUILD)/disk/disk.o   # <-- matches disk.asm
STAGE2_OBJ = $(BUILD)/stage2.o
OBJ = $(STAGE2_OBJ) $(DISK_C_OBJ) $(DISK_ASM_OBJ)

all: $(STAGE2_BIN)

# Compile stage2.c
$(STAGE2_OBJ): $(STAGE2_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

# Compile disk.c
$(DISK_C_OBJ): $(DISK_C_SRC)
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

# Assemble disk.asm
$(DISK_ASM_OBJ): $(DISK_ASM_SRC)
	mkdir -p $(dir $@)
	$(ASM) $(ASM_FLAGS) $< -o $@

# Link ELF
$(STAGE2_ELF): $(OBJ)
	$(LD) $(LD_FLAGS) $(OBJ) -o $@

# Convert to flat binary
$(STAGE2_BIN): $(STAGE2_ELF)
	i686-elf-objcopy -O binary $< $@

clean:
	rm -rf $(OBJ) $(STAGE2_ELF) $(STAGE2_BIN)

.PHONY: all clean
