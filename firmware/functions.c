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

#include "smart-psu.h"

void setupHardware (void ) {

	// Set ports direction
	setBit(D_PORT,FAULT);   // Fault alarm
	setBit(D_PORT,PWR);     // MOSFET Trigger
	setBit(D_PORT,GPIO);    // To SBC GPIO
	clearBit(D_PORT,PWR_SW);
	// Pullup resistor on button pin
	setBit(O_PORT,PWR_SW);

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
		_delay_ms(1);
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
	// Start timer clk/1024
#if defined (__AVR_ATmega328P__)
	TCCR0B = 0x01;
#else
	TCCR0 = 0x01;
#endif
}

void stopTimer(void) {
	ms_seconds = 0x0000;
	ticks = 0;
#if defined (__AVR_ATmega328P__)
	TCCR0B = 0x00;
#else
	TCCR0 = 0x00;
#endif
}

/* 
 * Blinking FAULT led forever
 */
inline void fault(void) {
	while(1) {
		_delay_ms(200);
		O_PORT ^= FAULT_MASK;
	}
}
