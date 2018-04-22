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
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>

#include "psud.h"

FILE *lockfile;

void psud_quit(int r) {
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
    struct psu_config config;
    memset(&config, 0, sizeof(config));
    if (( get_config(CONFILE, &config)) == -1 ) {
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
    int psu_pin = atoi(config.pin);
    int buttonstate=UP;

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

    // Polling for key pressed
    while(1) {
        buttonstate = gpio_pin_get(handle, psu_pin);
        if ( buttonstate == DOWN ) {

            pid_t pid=0;
            if ((pid = fork()) == -1)
                perror("fork error");
            else if (pid == 0) {
                syslog(LOG_NOTICE, "GPIO Toggle: Executing PSUD_CMD (%s).\n", (char*)config.cmd);
                execl("/bin/sh", "sh", "-c", (char*)config.cmd, NULL);
                syslog(LOG_NOTICE, "execl error\n");

            } 
            if (strcmp(config.opt, "WaitAndShoot") == 0 ) {
                    syslog(LOG_NOTICE, "Waiting child process(%d).\n", pid);
                    waitpid(pid, NULL, WEXITED);
                    syslog(LOG_NOTICE, "Toggling output pin.\n");
                    gpio_pin_output(handle, psu_pin);
                    gpio_pin_low(handle, psu_pin);
                    psud_quit(15);
            }
            wait(&status);
        }
        usleep(250000);
    }	
}

