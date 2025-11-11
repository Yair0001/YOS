BIN = ../../../bin
BUILD = ../../../build

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
