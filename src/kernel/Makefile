OUTPUT = $(BIN)/kernel.bin

C_SRC = main.c
COMMON_OBJS = $(BUILD)/common/intconv.o $(BUILD)/common/printk.o $(BUILD)/common/symbol.o

C_OBJS = $(BUILD)/kernel/main.o

ALL_OBJS = $(C_OBJS) $(COMMON_OBJS)

all: $(OUTPUT)

$(BUILD)/kernel:
	@mkdir -p $(BUILD)/kernel

$(BUILD)/kernel/main.o: main.c main.h | $(BUILD)/kernel
	$(CC) $(CC_FLAGS) -c main.c -o $(BUILD)/kernel/main.o

$(OUTPUT): $(ALL_OBJS) linker.ld
	$(LD) $(LD_FLAGS) $(ALL_OBJS) -o $(OUTPUT)
	@echo "Kernel built: $(OUTPUT)"

clean:
	rm -rf $(BIN)/kernel
	rm -rf $(BUILD)/kernel
	rm -f $(OUTPUT)

.PHONY: all clean