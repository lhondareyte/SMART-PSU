/*
 * Copyright (c) 2018-2021 Luc Hondareyte
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
