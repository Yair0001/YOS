
STAGE1_BIN = $(BIN)/stage1.bin
STAGE1_SRC = stage1.asm
KERNEL_SECTORS_FILE = $(BUILD)/kernel_sectors.txt

all: $(STAGE1_BIN)

$(STAGE1_BIN): $(STAGE1_SRC)
	@echo "ASM: $<"
	@mkdir -p $(BIN)
	@if [ -f "$(KERNEL_SECTORS_FILE)" ]; then \
		KERNEL_SECTORS=$$(cat $(KERNEL_SECTORS_FILE)); \
		echo "Building stage1 with KERNEL_SECTORS=$$KERNEL_SECTORS"; \
		$(ASM) -f bin -DKERNEL_SECTORS=$$KERNEL_SECTORS $< -o $@; \
	else \
		echo "Building stage1 without KERNEL_SECTORS (using fallback)"; \
		$(ASM) -f bin $< -o $@; \
	fi

clean:
	rm -f $(STAGE1_BIN)

.PHONY: all clean
