.PHONY: all clean stage1 stage2

STAGE1_BIN = $(BIN)/stage1.bin
STAGE2_BIN = $(BIN)/stage2.bin
BOOT_BIN = $(BIN)/boot.bin

all: stage1 stage2
	cat $(STAGE1_BIN) $(STAGE2_BIN) > $(BOOT_BIN)

stage1:
	$(MAKE) -C stage1

stage2:
	$(MAKE) -C stage2

clean:
	$(MAKE) -C stage1 clean
	$(MAKE) -C stage2 clean
	rm -fr $(BOOT_BIN)

.DEFAULT_GOAL := all