#
# $Id: Makefile,v 1.4 2011/04/25 16:21:03 luc Exp luc $
#

default: all

include config.mk

CC         = avr-gcc
OBJCOPY    = avr-objcopy
CFLAGS    += -Os -g -mmcu=$(MCU) -Wall -Wstrict-prototypes
ASMFLAGS   = -Os -mmcu=$(MCU) -x assembler-with-cpp -gstabs
ASMFLAGS  += -I /usr/local/avr/include

all: $(FIRMWARE).hex $(FIRMWARE).bin

coffee: all load wfuse mrproper
	@echo "All is nice. Have a good day!"

$(FIRMWARE).hex: $(FIRMWARE).out
	@printf "Generating $(FIRMWARE).hex ... "
	@$(OBJCOPY) -R .eeprom -O ihex $(FIRMWARE).out  \
		$(FIRMWARE).hex
	@echo "done."

$(FIRMWARE).out: $(OBJECTS) $(HEADERS) $(SOURCES)
	@printf "Linking $(FIRMWARE) ... "
	@$(CC) $(CFLAGS) -o $(FIRMWARE).out \
		-Wl,-Map,$(FIRMWARE).map $(OBJECTS)
	@echo "done."

.c.o:
	@printf "Compiling $< ... "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "done."

.s.o:
	@printf "Compiling $< ... "
	@$(CC) $(ASMFLAGS) -c $< -o $@
	@echo "done."

asm: $(FIRMWARE).out
	@printf "Generating assembler source file ... "
	@$(CCPATH)/avr-objdump -D -S $(FIRMWARE).out > $(FIRMWARE).s
	@echo "done."

$(FIRMWARE).bin: $(FIRMWARE).out 
	@printf "Generating $(FIRMWARE).bin ... "
	@$(OBJCOPY) -R .eeprom -O binary $(FIRMWARE).out  \
		$(OBJCOPY_OPTS) $(FIRMWARE).bin
	@echo "done."
load:
	@printf "Loading firmware..."
	@$(LOAD) > /dev/null 2>&1
	@echo "done."
dump:
	@printf "Reading $(MCU) device..."
	@$(DUMP) > /dev/null 2>&1
	@echo "done."
rfuse:
	@printf "Reading fuse..."
	@$(RFUSE) > /dev/null 2>&1
	@echo "done."

wfuse: fuses.txt
	@printf "Writing fuse..."
	#@$(WFUSE) > /dev/null 2>&1
	$(WFUSE)
	@echo "done."
#
# Nettoyage, Archivage, etc.
clean :
	@printf "Cleaning source tree..."
	@rm -f *.map *.bin *~ *.out *.gch *.o \
		low.txt high.txt $(FIRMWARE) $(FIRMWARE).asm *.hex fuses.???
	@echo "done."

#EOF
