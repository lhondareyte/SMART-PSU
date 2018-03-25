#
# Copyright (c)2017, Luc HONDAREYTE
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or 
# without modification, are permitted provided that the 
# following conditions are met:
# 1. Redistributions of source code must retain the above 
#    copyright notice, this list of conditions and the 
#    following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
# CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, 
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# $Id: Makefile,v 1.4 2011/04/25 16:21:03 luc Exp luc $
#

include config.mk

CCPATH		:=/usr/local/CrossPack-AVR/bin
CC		:=$(CCPATH)/avr-gcc
OBJCOPY		:=$(CCPATH)/avr-objcopy
CFLAGS		+=-Os 
CFLAGS		+=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes
CFLAGS		+=-D __BREADBOARD__

HEADERS         += $(shell ls *.h)
SOURCES         += $(shell ls *.c)
#ASMSRCS         += $(shell ls *.s)
OBJECTS         += $(patsubst %.c,%.o,$(SOURCES))
OBJECTS		+= $(patsubst %.s,%.o,$(ASMSRCS))
ASMFLAGS	:=-Os -mmcu=$(MCU) -x assembler-with-cpp -gstabs
ASMFLAGS	+=-I /usr/local/avr/include

all: $(FIRMWARE).hex 

coffee: all load verify wfuse mrproper
	@echo "All is nice. Have a good day."

$(FIRMWARE).hex: $(FIRMWARE).out $(HEADERS) $(SOURCES)
	@printf "Generating $(FIRMWARE).hex ... "
	@$(OBJCOPY) -R .eeprom -O ihex $(FIRMWARE).out  \
		$(FIRMWARE).hex
	@echo "done."

$(FIRMWARE).out: $(OBJECTS)
	@printf "Linking $(FIRMWARE) ... "
	@$(CC) $(CFLAGS) -o $(FIRMWARE).out \
		-Wl,-Map,$(FIRMWARE).map $(OBJECTS)
	@echo "done."

.c.o:  $(HEADERS) $(SOURCES)
	@printf "Compiling $< ... "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "done."

.s.o: $(HEADERS) $(ASMSRCS)
	@printf "Compiling $< ... "
	@$(CC) $(ASMFLAGS) -c $< -o $@
	@echo "done."

asm: $(FIRMWARE).out
	@printf "Generating assembler source file ... "
	@$(CCPATH)/avr-objdump -D -S $(FIRMWARE).out > $(FIRMWARE).s
	@echo "done."

bin: $(FIRMWARE).out 
	@printf "Generating $(FIRMWARE).bin ... "
	@$(OBJCOPY) -R .eeprom -O binary $(FIRMWARE).out  \
		$(FIRMWARE).bin
	@echo "done."
	@ls -l $(FIRMWARE).bin
#
# Configuration du programmateur ISP
LOADER=	avrdude
ISP	:=-c usbasp

LOADER	:=$(LOADER) -p $(MCU) $(ISP)
LOAD	:=$(LOADER) -i 5 -U flash:w:$(FIRMWARE).hex
DUMP	:=$(LOADER) -i 5 -U flash:r:$(FIRMWARE).hex:i
VERIFY	:=$(LOADER) -i 5 -U flash:v:$(FIRMWARE).hex
ERASE	:=$(LOADER) -i 5 -e
RFUSE	:=$(LOADER) -U lfuse:r:low.txt:h -U hfuse:r:high.txt:h -U efuse:r:extd.txt:h
WFUSE	:=$(LOADER) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

load:
	@printf "Loading firmware..."
	@minipro -S -w smart-psu.bin -c code -p ATTINY13 > /dev/null 2>&1
	@echo "done."
dump:
	@printf "Reading $(MCU) device..."
	@$(DUMP) > /dev/null 2>&1
	@echo "done."
verify:
	@printf "Verify $(MCU) device..."
	@$(VERIFY) > /dev/null 2>&1
	$(VERIFY) 
	@echo "done."
erase:
	@printf "Erasing $(MCU) device..."
	@$(ERASE) > /dev/null 2>&1
	@echo "done."
rfuse:
	@printf "Reading fuse..."
	@$(RFUSE) > /dev/null 2>&1
	@echo "done."
wfuse:
	@printf "Writing fuse..."
	@minipro -w fuses.txt -c config -p ATTINY13 > /dev/null 2>&1
	@echo "done."
dload:
	$(LOAD) 
dfuse:
	$(WFUSE)
#
# Nettoyage, Archivage, etc.
clean :
	@printf "Cleaning source tree..."
	@rm -f *.map *.bin *~ *.out *.gch *.o \
		low.txt high.txt $(FIRMWARE) $(FIRMWARE).asm *.hex
	@echo "done."

#EOF
