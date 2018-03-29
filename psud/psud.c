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

#if defined(__DEBUG__)
			fprintf(stderr, "execl: %s\n", buttond.cmd);
#endif
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

