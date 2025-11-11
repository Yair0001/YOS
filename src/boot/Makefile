# Gets BIN as parameter from parent Makefile

all: $(BOOT_IMG)

$(BOOT_IMG): $(STAGE1_BIN) $(STAGE2_BIN)
	cat $(STAGE1_BIN) $(STAGE2_BIN) > $@
	dd if=/dev/zero bs=512 count=8 >> $@ 2>/dev/null

$(STAGE1_BIN):
	$(MAKE) -C stage1 BIN=$(BIN)

$(STAGE2_BIN):
	$(MAKE) -C stage2 BIN=$(BIN)