#
# $Id: Makefile,v 1.4 2011/04/25 16:21:03 luc Exp luc $
#

FIRMWARE   = smart-psu
#MCU        = atmega328p
MCU        = attiny13
HEADERS   += smart-psu.h
SOURCES   += smart-psu.c functions.c
OBJECTS   += smart-psu.o functions.o

include Mk/$(MCU).mk

#CFLAGS    += -D__BREADBOARD__
CFLAGS    += -D__ACRECOVERY__
