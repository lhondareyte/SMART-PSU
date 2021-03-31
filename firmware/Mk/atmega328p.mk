#
# Copyright (c) 2006-2011 Luc HONDAREYTE
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

LFUSE   = 0xff
HFUSE   = 0xdf
EFUSE   = 0x05
CFLAGS += -D__BREADBOARD__
FLASHER = usbtiny
LOADER  = avrdude -q -p $(MCU) -c $(FLASHER) -i 5 -U flash:w:$(FIRMWARE).hex
RFUSE   = avrdude -q -p $(MCU) -c $(FLASHER) -U lfuse:r:low.txt:b -U hfuse:r:high.txt:b
WFUSE   = avrdude -q -p $(MCU) -c $(FLASHER) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m
DUMP    = avrdude -q -p $(MCU) -c $(FLASHER) -i 5 -U flash:r:$(FIRMWARE).hex:i

