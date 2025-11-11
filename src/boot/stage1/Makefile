# Gets BIN and ASM parameters from parent Makefile
STAGE1_BIN = $(BIN)/stage1.bin
STAGE1_SRC = src/boot/stage1/stage1.asm

all: $(STAGE1_BIN)

$(STAGE1_BIN): $(STAGE1_SRC)
	$(ASM) -f bin $< -o $@

clean:
	rm -fr $(STAGE1_BIN)