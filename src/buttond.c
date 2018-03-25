#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgpio.h>
#include <time.h>

#include "buttond.h"

int main(int argc, char **argv)
{
	struct buttond_config buttond;
	if (( get_config(CONFILE, &buttond)) == -1 ) {
		return 1;
	}

	int button_pin = atoi(buttond.pin);
	int buttonstate=0;
	int lastbuttonstate=0;

	gpio_handle_t handle;
	handle = gpio_open(0);
	gpio_pin_input(handle, button_pin);
	gpio_pin_low(handle, button_pin);
	gpio_pin_pullup(handle, button_pin);

#if defined(__DEBUG__)
	fprintf(stderr, "Button Pin: %s\nButton command: %s\n", buttond.pin, buttond.cmd);
	int led_pin = 0;
	int ledstate = GPIO_PIN_LOW;
	gpio_pin_output(handle, led_pin);
	gpio_pin_low(handle, led_pin);
#endif	
	lastbuttonstate = gpio_pin_get(handle, button_pin);

	// Polling for key pressed
	while(1) {
		buttonstate = gpio_pin_get(handle, button_pin);
		if (lastbuttonstate != buttonstate) {
			lastbuttonstate = buttonstate;
			usleep(150000);

#if defined(__DEBUG__)
			fprintf(stderr, "execl: %s\n", buttond.cmd);
#endif
			execl ( "/sbin/shutdown", "shutdown", "-p", "now", NULL);
		}
		else {
			lastbuttonstate = buttonstate;
		}
		usleep(100000);
	}	
}

