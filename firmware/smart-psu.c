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
/*
 * POWER BUTTON - AVR Version
 *
 * Copyright (c)2018-2021, Luc Hondareyte
 * All rights reserved.
 *
 * $Id$
 */

#include "smart-psu.h"

uint8_t pwr_state=OFF;
uint8_t os_is_running=NO;

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
	setBit(D_PORT,GPIO);      // no need feedback from SBC
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

/* Blinking a led */

inline void blink (uint8_t pin, uint8_t n) {
	while(n) {
		ms_wait(250);
		toggleBit(O_PORT, pin);
		n--;
	}
	clearBit(O_PORT, pin);
}

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

ISR (INT0_vect) {
	// Wake-up MCU on key pressed
}

#if defined (__AVR_ATtiny13A__) || defined (__AVR_ATtiny13__)
ISR (TIM0_OVF_vect)
#else
ISR (TIMER0_OVF_vect)
#endif
{
	ticks++;
	if ( ticks == TICKS ) {
		ticks = 0;
		ms_seconds--;
	}
}

static void Power (void) {

	/*  Board is ON */

	if (pwr_state == ON) {
		if (os_is_running == YES) {
			setBit(O_PORT,FAULT);
			shutdown();
			startTimer(SHUTDOWN_TIMEOUT);
			while ( ms_seconds > 0 ) {
				if (bit_is_set(I_PORT,GPIO)) {
					stopTimer();
				       	break;
				}
			}
			pwr_state=OFF;
#if defined (__AC_RECOVERY__)
			saveConfiguration(pwr_state);
#endif
			os_is_running=NO;
			clearBit(O_PORT,FAULT);
			PowerOff();
			clearBit(O_PORT,FAULT);
		}
	
	}
	/* Board is OFF */
	else {
		switchOn();
		pwr_state=ON;
#if defined (__AC_RECOVERY__)
		saveConfiguration(pwr_state);
#endif
		loop_until_bit_is_set(I_PORT,PWR_SW);
		ms_wait(250);
		os_is_running=YES;
		startTimer(STARTUP_TIMEOUT);
#if defined (__BREADBOARD__)
		setBit(O_PORT,FAULT);
#endif
		while (ms_seconds > 0) {
			if ( bit_is_clear(I_PORT,PWR_SW)) {
				stopTimer();
				pwr_state=OFF;
#if defined (__AC_RECOVERY__)
				saveConfiguration(pwr_state);
#endif
				switchOff();
				alarm(10);
				break;
			}
		}
#if defined (__BREADBOARD__)
		clearBit(O_PORT,FAULT);
#endif
	}
	stopTimer();
}

int main(void) {

	ticks = 0;
	ms_seconds = 0;
	setupHardware();

	/* Wait for PSU stabilization */
        blink (PWR, 8);

#if defined (__AC_RECOVERY__)
	if (bit_is_set(I_PORT, ACR)) {
		pwr_state=OFF;
	}
	else {
		pwr_state = loadConfiguration();
		if ( pwr_state > 0x00 ) pwr_state = ON;
	}
#else
	pwr_state=OFF;
#endif
	os_is_running=NO;
	switchOff();
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	/*
	 * main loop
	 */
	while (1) {
		enable_INT0();
		sleep_enable();
		sei();
		sleep_cpu();
		/*
		 * zzzzz
		 */
		sleep_disable();
		disable_INT0();
		Power();
		loop_until_bit_is_set(I_PORT,PWR_SW);
		_delay_ms(250);
	}
}
