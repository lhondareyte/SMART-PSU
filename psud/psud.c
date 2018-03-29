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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgpio.h>
#include <time.h>

#include "psud.h"

int main(int argc, char **argv) {
	struct psu_config config;
	if (( get_config(CONFILE, &config)) == -1 ) {
		return 1;
	}

	int psu_pin = atoi(config.pin);
	int buttonstate=0;
	int lastbuttonstate=0;

	gpio_handle_t handle;
	handle = gpio_open(0);
	gpio_pin_input(handle, psu_pin);
	gpio_pin_low(handle, psu_pin);
	gpio_pin_pullup(handle, psu_pin);

#if defined(__DEBUG__)
	fprintf(stderr, "PSU Pin: %s\nButton command: %s\n", config.pin, config.cmd);
	int led_pin = 0;
	int ledstate = GPIO_PIN_LOW;
	gpio_pin_output(handle, led_pin);
	gpio_pin_low(handle, led_pin);
#endif	
	lastbuttonstate = gpio_pin_get(handle, psu_pin);

	// Polling for key pressed
	while(1) {
		buttonstate = gpio_pin_get(handle, psu_pin);
		if (lastbuttonstate != buttonstate) {
			lastbuttonstate = buttonstate;
			usleep(150000);

			pid_t pid=0;
			if ((pid = fork()) == -1)
				perror("fork error");
			else if (pid == 0) {
				execl("/bin/sh", "sh", "-c", (char*)config.cmd, NULL);
				fprintf(stderr, "execl error\n");
			}
		}
		else {
			lastbuttonstate = buttonstate;
		}
		usleep(100000);
	}	
}

