# SMART PSU for ARM SBC
This is a smart power switch for ARM SBC. This provides a gracefull shutdown and power-off for any tiny board computer that support FreeBSD+libgpio.

This tested OK on 
* Nanopi Neo
* Nanopi Neo Air
* Orange PI
* Raspberry PI B
* Raspberry PI 3

## How it's work?
When plugging in, the board is poweroff and the switch device enter in sleep mode to reduce power consomption.  Just press the switch to power on the board. If you press again the button within 1.5 seconds, the board is poweroff immediatly. 

In normal operation (when operating system is running), the ```psud``` daemon wait for key pressed to perform specified action. The default configuration file is as follow:

```
# psud configuration file
# $Id$  /etc/psud.conf
PSUD_PIN=3                       # My configuration on NanoPI Neo
PSUD_CMD="/sbin/shutdown -p now"	
PSUD_OPT="Dont Care"             # Nothing special
```
In ```/etc/rc.conf```, adds the following line

```
psud_enable="YES"
```
Start ```psud``` 

```
service psud start
```
So, just press button to gracefully shutdown the system. After the configured delay (by dip-switch), the board is powered-off.

## AC Recovery mode
AC Power Recovery
Allows you to set how the system reacts after AC power is restored to the system. By default, the AC Power Recovery option is set to last state. The other option is "power off".

## Nanobsd configuration
Since all persistents filesystems are mount read-only, there is no need for graceful shutdown with nanobsd. But you probably need to save your configuration on shutdown. You can achieve this with the following script:

```
#!/bin/sh
#
# file: /usr/local/bin/save_configuration.sh
#
mount /cfg || exit 1
find /cfg -type f -print | sed -e '/^\/cfg//' | while read f
do
	if [ -f /etc/$f ] ; then
		cp -p /etc/$f /cfg/$f
	fi
done
sync;sync;sync
umount /cfg
```
Edit ```/etc/psud.conf``` as follows:

```
PSUD_PIN=1                    # Hardware dependent
PSUD_CMD="/usr/local/bin/save_nanobsd.sh"

PSUD_OPT="WaitAndShot"        # Wait for $PSUD_CMD to complete before
                              # poweroff. GPIO pin is toggle to HIGH 
                              # after $CMD complete
```

## About files
```
 psud      psud daemon sources
 kicad     KiCad schematic
 firmware  source code AVR attiny13/13a and atmega328p
 refs      Datasheets
```
## LICENSE
Released under the ISC Public License
