/*
 * Copyright (c)2018, Luc Hondareyte
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
#ifndef __POWER_BUTTON_H__
 #define __POWER_BUTTON_H__

#include <avr/io.h>

#define  setBit(octet,bit)     ( octet |= (1<<bit))
#define  clearBit(octet,bit)   ( octet &= ~(1<<bit))

#if defined (__AVR_ATtiny13A__)  || defined (__AVR_ATtiny13__)

#undef F_CPU
#define F_CPU	4800000UL
/* Interupt mask register */
#define INTMSKR	GIMSK
/* Interrupt register */
#define INTRGST	MCUCR

#define D_PORT	DDRB
#define PORT	PORTB
#define IPORT	PINB
#define PWR	0
#define BUTTON	1
#define LED	2
#define FAULT	3
#define DELAY	4

#elif defined (__AVR_ATmega328P__)

#undef F_CPU
#define F_CPU	16000000UL
/* Interupt mask register */
#define INTMSKR	EIMSK
/* Interrupt register */
#define INTRGST	EICRA

#define D_PORT	DDRD
#define PORT	PORTD
#define IPORT	PIND
#define BUTTON	2
#define PWR	3
#define PWRDWN	4
#define LED	5
#define HB	6

#else
 #error "Device not supported"
#endif

#if defined (__BREADBOARD__)
#define switchOn(n)	setBit(PORT,n)
#define switchOff(n)	clearBit(PORT,n)
#else
#define switchOn(n)	clearBit(PORT,n)
#define switchOff(n)	setBit(PORT,n)
#endif

#define NO	0
#define YES	1
#define PWR_OFF	0
#define PWR_ON	1

#endif /* __POWER_BUTTON_H__ */
