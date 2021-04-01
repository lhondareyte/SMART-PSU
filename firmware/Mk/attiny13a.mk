#
# $Id$
#

FIRMWARE     = smart-psu
#MCU         = attiny13a
MCU          = attiny13
LFUSE        = 0x71
HFUSE        = 0xff
LOAD         = minipro -P -w $(FIRMWARE).bin -c code -p ATTINY13
RFUSE        = minipro -r fuses.TXT -c config -p ATTINY13
WFUSE        = minipro -w fuses.txt -c config -p ATTINY13
DUMP         = minipro -S -r $(FIRMWARE).bin -c code -p ATTINY13
OBJCOPY_OPTS = --gap-fill=0xff --pad-to=0x400
FUSES        = fuses.txt

fuses.txt:
	@echo "fuses_lo = $(LFUSE)"  > $(FUSES)
	@echo "fuses_hi = $(HFUSE)" >> $(FUSES)
	@echo "lock_byte = 0xff"    >> $(FUSES)
