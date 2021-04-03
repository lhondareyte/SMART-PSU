/*
 * Copyright (c)2018-2021, Luc Hondareyte
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

#define F_CPU		4800000UL

#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>

/*
 * Hardware Configuration
 */

#if defined (__AVR_ATtiny13A__)  || defined (__AVR_ATtiny13__)

#undef F_CPU
#define F_CPU		4800000UL
#define INTMSKR		GIMSK		// Interupt mask register
#define INTRGST		MCUCR		// Interrupt register

#define D_PORT		DDRB
#define O_PORT		PORTB
#define I_PORT		PINB
#define GPIO		0
#define PWR_SW		1
#define PWR		2
#define FAULT		3
#define DELAY		4
#define ACR		5
#define LED_MASK	4
#define FAULT_MASK	8
#define TICKS		16

#elif defined (__AVR_ATmega328P__)

#undef F_CPU
#define F_CPU		16000000UL
#define INTMSKR		EIMSK		// Interupt mask register
#define INTRGST		EICRA		// Interrupt register 

#define D_PORT		DDRD
#define O_PORT		PORTD
#define I_PORT		PIND
#define PWR_SW		2
#define GPIO		3
#define PWR		4
#define DELAY		5
#define FAULT		6
#define ACR		7
#define LED_MASK	4
#define FAULT_MASK	8
#define TICKS		66

#else
 #error "Device not supported"
#endif

/*
 * Macros
 */
#define STATUS		1

#define loadConfiguration()	 eeprom_read_byte((uint8_t *)STATUS)
#define saveConfiguration(n)	 eeprom_write_byte((uint8_t *)STATUS,n)

#define setBit(octet,bit)     ( octet |= (1<<bit))
#define clearBit(octet,bit)   ( octet &= ~(1<<bit))
#define toggleBit(octet,bit)  ( octet ^= (1<<bit))
#define enable_INT0()         setBit(INTMSKR,INT0)
#define disable_INT0()        clearBit(INTMSKR,INT0)

#if defined (__BREADBOARD__)
  #define switchOn()	setBit(O_PORT,PWR)
  #define switchOff(n)	clearBit(O_PORT,PWR)
#else
  #define switchOn()	clearBit(O_PORT,PWR)
  #define switchOff()	setBit(O_PORT,PWR)
#endif

/*
 * Misc
 */
#define NO			0
#define YES			1
#define OFF			0
#define ON			1
#define SHUTDOWN_TIMEOUT	5000    // Time to wait before force power off (ms)
#define STARTUP_TIMEOUT		1500    // Time before startup that we can force poweroff (ms)

uint16_t volatile ms_seconds;
uint8_t volatile ticks;

/*
 * Prototypes
 */
void alarm(uint8_t);
void setupHardware(void);
void store(void);
void shutdown(void);
void ms_wait(uint8_t);
void startTimer(uint16_t);
void stopTimer(void);
void PowerOff(void);

#endif /* __POWER_BUTTON_H__ */
