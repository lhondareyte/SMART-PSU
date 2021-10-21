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

#include "smart-psu.h"

void setupHardware (void ) {

	// Set ports direction
	setBit(D_PORT,FAULT);     // Fault alarm
	setBit(D_PORT,PWR);       // MOSFET Trigger
	setBit(D_PORT,GPIO);      // To SBC GPIO
	clearBit(D_PORT,PWR_SW);  // Power switch
	clearBit(D_PORT,ACR);     // AC Recovery mode
	// Pullup resistor on input pins
	setBit(O_PORT,PWR_SW);
	setBit(O_PORT,ACR);

	// Configure INT0
	clearBit(INTRGST,ISC00);
	clearBit(INTRGST,ISC01);
	enable_INT0();
#if defined (__BREADBOARD__)
	CLKPR=0x00;
#endif

	// Configure TIMER0 interuption
	TIMSK0 |= (1<<TOIE0);
}

void ms_wait (uint8_t n) {
	while (n) {
		_delay_us(1000);
		n--;
	}
}

inline void shutdown (void) {
#if defined (__BREADBOARD__)
	setBit(O_PORT,GPIO);
	ms_wait(250);
	clearBit(O_PORT,GPIO);
#else
	clearBit(O_PORT,GPIO);
	ms_wait(250);
	setBit(O_PORT,GPIO);
#endif
	ms_wait(250);
	clearBit(D_PORT,GPIO);    // Wait feedback from SBC
}


inline void PowerOff (void) {
	clearBit(O_PORT,GPIO);
	setBit(D_PORT,GPIO);    // no need feedback from SBC
	switchOff();
}

void startTimer (uint16_t n) {
	ms_seconds = n;
	ticks = 0;
	// No prescaler
	TCCR0B = 0x01;
}

void stopTimer(void) {
	ms_seconds = 0x0000;
	ticks = 0;
	TCCR0B = 0x00;
}

/* 
 * Blinking alarm led
 */
inline void alarm (uint8_t n) {
	while(n) {
		ms_wait(200);
		toggleBit(O_PORT, FAULT);
		n--;
	}
}
