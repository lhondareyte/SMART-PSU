#
# $Id$
#

LFUSE   = 0xff
HFUSE   = 0xdf
EFUSE   = 0x05
CFLAGS += -D__BREADBOARD__

FLASHER = usbtiny
LOADER  = avrdude -q -p $(MCU) -c $(FLASHER)
LOAD    = $(LOADER) -i 5 -U flash:w:$(FIRMWARE).hex
RFUSE   = $(LOADER) -U lfuse:r:low.txt:b -U hfuse:r:high.txt:b
WFUSE   = $(LOADER) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m
DUMP    = $(LOADER) -i 5 -U flash:r:$(FIRMWARE).hex:i

fuses.txt:
	touch $@

