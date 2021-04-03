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
	/*
	 *  Board is ON
	 */
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
#if defined (__ACRECOVERY__)
			saveConfiguration(pwr_state);
#endif
			os_is_running=NO;
			clearBit(O_PORT,FAULT);
			PowerOff();
			clearBit(O_PORT,FAULT);
		}
	
	}
	/*
	 *  Board is OFF
	 */
	else {
		switchOn();
		pwr_state=ON;
#if defined (__ACRECOVERY__)
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
#if defined (__ACRECOVERY__)
				saveConfiguration(pwr_state);
#endif
				switchOff();
				alarm(12);
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
#if defined (__ACRECOVERY__)
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
