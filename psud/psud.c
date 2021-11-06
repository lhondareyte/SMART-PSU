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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgpio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

#include "psud.h"
#include "config.h"

FILE *lockfile;

struct config psu_config;

void psud_quit(int r) {
	if ( r == SIGHUP ) {
		get_config(CONFILE, &psu_config);
		syslog(LOG_NOTICE,"Waiting on pin %s for action (%s/%s).\n", psu_config.pin, psu_config.cmd, psu_config.opt);
		return;
	}
	syslog(LOG_NOTICE,"Signal received (%d), quitting.\n", r);
	fclose(lockfile);
	remove (LOCK);
	closelog();
	exit(0);
}

int main(int argc, char **argv) {

	int status=0;

	/*
	 * Open exclusive lock file to avoid multiple instances of daemon
	 */
	if (( lockfile = fopen(LOCK, "w")) == NULL) {
		perror(LOCK);
		return 1;
	}
	if (flock (fileno(lockfile), LOCK_EX | LOCK_NB) == -1) {
		perror (LOCK);
		return 1;
	}

	/*
	 * Getting valid configuration
	 */
	if (( get_config(CONFILE, &psu_config)) == -1 ) {
		fprintf (stderr, "Error getting configuration.\n");
		return 1;
	}

	/*
	 * Logging
	 */
	openlog("psud", LOG_PID|LOG_NDELAY, LOG_DAEMON),
		syslog(LOG_NOTICE, "Starting daemon.\n");

	/*
	 * Signals handling
	 */
	signal(SIGHUP, psud_quit);
	signal(SIGINT, psud_quit);
	signal(SIGTERM, psud_quit);

	/*
	 * Daemonize
	 */
	pid_t process_id=0;
	if ((process_id = fork()) < 0) {
		perror("fork");
		exit(1);
	}
	// Kill parent process
	if (process_id > 0 )
		exit(0);

	/*
	 * Writing pid to lockfile
	 */
	setvbuf (lockfile, (char*)NULL, _IONBF, 0);
	pid_t pid=getpid();
	fprintf(lockfile, "%d", pid);
	setpriority(PRIO_PROCESS, pid, 20);

	/*
	 * Ready to run. 
	 */
	int psu_pin = atoi(psu_config.pin);
	int buttonstate=UP;
	gpio_handle_t handle;
	if (( handle = gpio_open(0)) == -1) {
		syslog(LOG_NOTICE,"Error : No GPIO found on this platform.\n");
		//psud_quit(15);
	}

	gpio_pin_input(handle, psu_pin);
	gpio_pin_low(handle, psu_pin);
	gpio_pin_pullup(handle, psu_pin);

	syslog(LOG_NOTICE,"Waiting on pin %s for action (%s/%s).\n", psu_config.pin, psu_config.cmd, psu_config.opt);

	// Polling for key pressed
	while(1) {
		buttonstate = gpio_pin_get(handle, psu_pin);
		if ( buttonstate == DOWN ) {

			pid_t pid=0;
			if ((pid = fork()) == -1)
				perror("fork error");
			else if (pid == 0) {
				syslog(LOG_NOTICE, "GPIO %d toggle: Executing PSUD_CMD (%s).\n", psu_pin, (char*)psu_config.cmd);
				execl("/bin/sh", "sh", "-c", (char*)psu_config.cmd, NULL);
				syslog(LOG_NOTICE, "execl error\n");
				continue;

			} 
			if (strcmp(psu_config.opt, "WaitAndShoot") == 0 ) {
				syslog(LOG_NOTICE, "Waiting for child process(%d).\n", pid);
				waitpid(pid, NULL, WEXITED);
				// Toggle pin from ouput and high level to shutoff
				gpio_pin_output(handle, psu_pin);
				gpio_pin_high(handle, psu_pin);
				psud_quit(15);
			}
			wait(&status);
		}
		usleep(250000);
	}	
}

