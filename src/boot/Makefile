#### BOOTLOADER
BOOT_IMG = $(BIN)/boot.bin

STAGE1_BIN = $(BIN)/stage1.bin
STAGE2_BIN = $(BIN)/stage2.bin

all: $(BOOT_IMG)

$(BOOT_IMG): $(STAGE1_BIN) $(STAGE2_BIN)
	cp $< $@
	cat $(word 2, $^) >> $@
	dd if=/dev/zero bs=512 count=8 >> ./bin/os.bin

$(STAGE1_BIN):
	$(MAKE) -C stage1

$(STAGE2_BIN):
	$(MAKE) -C stage2

clean:
	$(MAKE) -C stage1 clean
	$(MAKE) -C stage2 clean
	rm -f $(BOOT_IMG)