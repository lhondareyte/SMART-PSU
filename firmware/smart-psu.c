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
/*
 * POWER BUTTON - AVR Version
 *
 * Copyright (c)2018, Luc Hondareyte
 * All rights reserved.
 *
 * $Id$
 */

#include "smart-psu.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/power.h>

// Time to wait operating systeme
#define STARTUP_TIMEOUT 20
#define SHUTDOWN_TIMEOUT 20

inline void setINT0(void) {
	setBit(INTMSKR,INT0);
}

inline void unsetINT0(void) {
	clearBit(INTMSKR,INT0);
}

inline void SetupHardware(void ) {

	// Set ports direction
	D_PORT=0x00;
	setBit(D_PORT,LED);
	setBit(D_PORT,PWR);
	// Pullup resistor on button pin
	setBit(PORT,BUTTON);

	// Configure INT0
	clearBit(INTRGST,ISC00);
	clearBit(INTRGST,ISC01);

	// Active INT0
	setINT0();
	sei();
}

uint8_t board_is_on=0;
uint8_t os_is_active=0;

uint8_t volatile seconds=0;
uint16_t volatile _ms=0x0000;

#if defined (__AVR_ATtiny13A__) || defined (__AVR_ATtiny13__)
ISR (TIM0_OVF_vect) {
#else
ISR (TIMER0_OVF_vect) {
#endif
}

ISR (INT0_vect) {
	// We just Wake-up CPU
}

inline void startTimer(void) {
}

inline void stopTimer(void) {
}

inline void waitForStartup(int t) {
}

inline void waitForShutdown(int t) {
}

uint8_t powerOn(void){
	uint8_t rc=0;
	//
	// Wait for key pressed
	//
	loop_until_bit_is_clear(IPORT,BUTTON);
	switchOn(PWR);
	_delay_ms(200);
	startTimer();
	//
	// Allow immediate power off within 3 seconds after power on
	//
	while ( seconds <= 3 ) {
		if ( bit_is_set (PORT,BUTTON) ) {
			switchOff(PWR);
			_delay_ms(200);
			rc=1;
			break;
		}
	}
	stopTimer();
	return(rc);
}

int main(void){

	SetupHardware();
	//
	// Power-down configuration
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	switchOff(PWR);
	board_is_on=NO;
	os_is_active=NO;
	while (1) {
		sleep_enable();
		sleep_mode();
		/* 
		   ...zzzzzzzzzzzz
		   Waiting for INT0.
		 */
		sleep_disable();
		unsetINT0();
		if (board_is_on) {
			if (os_is_active) {
				waitForShutdown(SHUTDOWN_TIMEOUT);
			}
			switchOff(PWR);
			board_is_on=NO;
		}
		else {
			switchOn(PWR);
			board_is_on=YES;
			//waitForStartup(STARTUP_TIMEOUT);
			//switchOff();
			//board_is_on=NO;
		}
		/*
		 *  Debounce
		 */
		loop_until_bit_is_set(IPORT,BUTTON);
		_delay_ms(200);

		setINT0();
	}
}

