STAGE1_SRC = stage1.asm
STAGE1_BIN = $(BIN)/stage1.bin

all: $(STAGE1_BIN)

$(STAGE1_BIN): $(STAGE1_SRC)
	$(ASM) -f bin $< -o $@

clean:
	rm -f $(STAGE1_BIN)
