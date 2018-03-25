EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:smart-psu-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "SMART-PSU"
Date "2017-12-17"
Rev "$Id$"
Comp "Luc Hondareyte"
Comment1 "PowerSwitch"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C_Small C4
U 1 1 5A367225
P 5800 3900
F 0 "C4" H 5700 4000 44  0000 L CNN
F 1 "100n" H 5600 3820 44  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 5800 3900 60  0001 C CNN
F 3 "" H 5800 3900 60  0000 C CNN
	1    5800 3900
	-1   0    0    -1  
$EndComp
Text Label 8800 3850 2    44   ~ 0
FAULT
Text Label 8800 3550 2    44   ~ 0
~PWRON
$Comp
L CP1_Small C3
U 1 1 5A36723B
P 5600 3900
F 0 "C3" H 5610 3970 50  0000 L CNN
F 1 "100u" H 5610 3820 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D7.5mm_P2.50mm" H 5600 3900 50  0001 C CNN
F 3 "" H 5600 3900 50  0001 C CNN
	1    5600 3900
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5A36723C
P 5600 4050
F 0 "#PWR01" H 5600 3800 50  0001 C CNN
F 1 "GND" H 5600 3900 50  0000 C CNN
F 2 "" H 5600 4050 50  0000 C CNN
F 3 "" H 5600 4050 50  0000 C CNN
	1    5600 4050
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 5A36723E
P 6650 5150
F 0 "#FLG02" H 6650 5225 50  0001 C CNN
F 1 "PWR_FLAG" H 6650 5300 50  0000 C CNN
F 2 "" H 6650 5150 50  0001 C CNN
F 3 "" H 6650 5150 50  0001 C CNN
	1    6650 5150
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG03
U 1 1 5A36723F
P 6200 5400
F 0 "#FLG03" H 6200 5475 50  0001 C CNN
F 1 "PWR_FLAG" H 6200 5560 50  0000 C CNN
F 2 "" H 6200 5400 50  0001 C CNN
F 3 "" H 6200 5400 50  0001 C CNN
	1    6200 5400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR04
U 1 1 5A367240
P 6650 5400
F 0 "#PWR04" H 6650 5150 50  0001 C CNN
F 1 "GND" H 6650 5250 50  0000 C CNN
F 2 "" H 6650 5400 50  0000 C CNN
F 3 "" H 6650 5400 50  0000 C CNN
	1    6650 5400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR05
U 1 1 5A367241
P 6200 5150
F 0 "#PWR05" H 6200 5000 50  0001 C CNN
F 1 "+5V" H 6200 5290 50  0000 C CNN
F 2 "" H 6200 5150 60  0000 C CNN
F 3 "" H 6200 5150 60  0000 C CNN
	1    6200 5150
	1    0    0    -1  
$EndComp
$Comp
L ATTINY13-20SSU U2
U 1 1 5A36742E
P 7100 3800
F 0 "U2" H 7900 4200 50  0000 C CNN
F 1 "ATTINY13-20SSU" H 7750 3400 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 7700 3800 50  0001 C CIN
F 3 "" H 6300 4150 50  0001 C CNN
	1    7100 3800
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5A367BD2
P 6050 4250
F 0 "#PWR06" H 6050 4000 50  0001 C CNN
F 1 "GND" H 6050 4100 50  0000 C CNN
F 2 "" H 6050 4250 50  0000 C CNN
F 3 "" H 6050 4250 50  0000 C CNN
	1    6050 4250
	1    0    0    -1  
$EndComp
Connection ~ 5600 3550
Wire Wire Line
	5800 3550 5800 3800
Connection ~ 5800 3550
$Comp
L LM2596 U1
U 1 1 5A37884F
P 4250 3650
F 0 "U1" H 4600 3450 60  0000 C CNN
F 1 "LM2596" H 4050 3950 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-263-5_TabPin6" H 4250 3650 60  0001 C CNN
F 3 "" H 4250 3650 60  0001 C CNN
	1    4250 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5A378850
P 4100 4050
F 0 "#PWR07" H 4100 3800 50  0001 C CNN
F 1 "GND" H 4100 3900 50  0000 C CNN
F 2 "" H 4100 4050 50  0001 C CNN
F 3 "" H 4100 4050 50  0001 C CNN
	1    4100 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 5A378851
P 4400 4050
F 0 "#PWR08" H 4400 3800 50  0001 C CNN
F 1 "GND" H 4400 3900 50  0000 C CNN
F 2 "" H 4400 4050 50  0001 C CNN
F 3 "" H 4400 4050 50  0001 C CNN
	1    4400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4050 4100 4000
Wire Wire Line
	4400 4050 4400 4000
$Comp
L L_Core_Ferrite_Small L1
U 1 1 5A378852
P 5050 3750
F 0 "L1" V 5150 3800 50  0000 L CNN
F 1 "33uH" V 5150 3600 44  0000 L CNN
F 2 "Choke_Toroid_ThroughHole:Choke_Toroid_6,5x13mm_Vertical" H 5050 3750 50  0001 C CNN
F 3 "" H 5050 3750 50  0001 C CNN
	1    5050 3750
	0    -1   -1   0   
$EndComp
$Comp
L D_Schottky_Small_ALT D1
U 1 1 5A378853
P 4900 3900
F 0 "D1" V 4900 3750 50  0000 L CNN
F 1 "1N5824" V 5000 3600 44  0000 L CNN
F 2 "Diodes_THT:D_DO-201AD_P12.70mm_Horizontal" V 4900 3900 50  0001 C CNN
F 3 "" V 4900 3900 50  0001 C CNN
	1    4900 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 3800 4900 3750
Connection ~ 4900 3750
$Comp
L GND #PWR09
U 1 1 5A378854
P 4900 4050
F 0 "#PWR09" H 4900 3800 50  0001 C CNN
F 1 "GND" H 4900 3900 50  0000 C CNN
F 2 "" H 4900 4050 50  0001 C CNN
F 3 "" H 4900 4050 50  0001 C CNN
	1    4900 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4050 4900 4000
$Comp
L CP1_Small C2
U 1 1 5A378855
P 5200 3900
F 0 "C2" H 5210 3970 50  0000 L CNN
F 1 "220u" H 5210 3820 44  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 5200 3900 50  0001 C CNN
F 3 "" H 5200 3900 50  0001 C CNN
	1    5200 3900
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5A378856
P 5200 4050
F 0 "#PWR010" H 5200 3800 50  0001 C CNN
F 1 "GND" H 5200 3900 50  0000 C CNN
F 2 "" H 5200 4050 50  0001 C CNN
F 3 "" H 5200 4050 50  0001 C CNN
	1    5200 4050
	1    0    0    -1  
$EndComp
Connection ~ 5200 3750
Wire Wire Line
	5200 4050 5200 4000
$Comp
L +5V #PWR011
U 1 1 5A378857
P 5200 3000
F 0 "#PWR011" H 5200 2850 50  0001 C CNN
F 1 "+5V" H 5200 3140 50  0000 C CNN
F 2 "" H 5200 3000 50  0001 C CNN
F 3 "" H 5200 3000 50  0001 C CNN
	1    5200 3000
	1    0    0    -1  
$EndComp
Connection ~ 5200 3550
$Comp
L CP1_Small C1
U 1 1 5A378858
P 3600 3900
F 0 "C1" H 3610 3970 50  0000 L CNN
F 1 "680u" H 3610 3820 44  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P5.00mm_P7.50mm" H 3600 3900 50  0001 C CNN
F 3 "" H 3600 3900 50  0001 C CNN
	1    3600 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5A378859
P 3600 4050
F 0 "#PWR012" H 3600 3800 50  0001 C CNN
F 1 "GND" H 3600 3900 50  0000 C CNN
F 2 "" H 3600 4050 50  0001 C CNN
F 3 "" H 3600 4050 50  0001 C CNN
	1    3600 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 4050 3600 4000
Wire Wire Line
	3600 3800 3600 3550
Connection ~ 3600 3550
$Comp
L Screw_Terminal_1x02 J1
U 1 1 5A37885A
P 3100 3650
F 0 "J1" H 3100 3900 50  0000 C TNN
F 1 "12V" V 2950 3650 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_4UCON_19963_02x3.5mm_Straight" H 3100 3425 50  0001 C CNN
F 3 "" H 3075 3650 50  0001 C CNN
	1    3100 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5A37885B
P 3350 4050
F 0 "#PWR013" H 3350 3800 50  0001 C CNN
F 1 "GND" H 3350 3900 50  0000 C CNN
F 2 "" H 3350 4050 50  0001 C CNN
F 3 "" H 3350 4050 50  0001 C CNN
	1    3350 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4050 3350 3750
Wire Wire Line
	3350 3750 3300 3750
Wire Wire Line
	3300 3550 3600 3550
Wire Wire Line
	3600 3550 3650 3550
Wire Wire Line
	5200 3750 5150 3750
Wire Wire Line
	4850 3750 4900 3750
Wire Wire Line
	4900 3750 4950 3750
Wire Wire Line
	5600 3400 5600 3550
Wire Wire Line
	5600 3550 5600 3800
$Comp
L 2N7002 Q1
U 1 1 5A381AB4
P 8350 3150
F 0 "Q1" V 8300 2850 50  0000 L CNN
F 1 "AOD4184A" V 8600 3000 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 8550 3075 50  0001 L CIN
F 3 "" H 8350 3150 50  0001 L CNN
	1    8350 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8800 3750 8100 3750
Text Label 8800 3050 2    44   ~ 0
LOAD
$Comp
L +5V #PWR014
U 1 1 5A3824C8
P 7600 3000
F 0 "#PWR014" H 7600 2850 50  0001 C CNN
F 1 "+5V" H 7600 3140 50  0000 C CNN
F 2 "" H 7600 3000 50  0001 C CNN
F 3 "" H 7600 3000 50  0001 C CNN
	1    7600 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3000 5200 3550
Wire Wire Line
	5200 3550 5200 3750
Wire Wire Line
	5200 3750 5200 3800
$Comp
L GND #PWR015
U 1 1 5A3827DD
P 5800 4050
F 0 "#PWR015" H 5800 3800 50  0001 C CNN
F 1 "GND" H 5800 3900 50  0000 C CNN
F 2 "" H 5800 4050 50  0000 C CNN
F 3 "" H 5800 4050 50  0000 C CNN
	1    5800 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4050 5800 4000
Wire Wire Line
	5600 4050 5600 4000
Text Label 8800 3650 2    44   ~ 0
~BUTTON
Wire Wire Line
	6200 5400 6200 5150
Wire Wire Line
	6650 5400 6650 5150
$Comp
L D_Schottky_Small_ALT D2
U 1 1 5A382D9D
P 5400 3550
F 0 "D2" H 5400 3450 50  0000 L CNN
F 1 "BAT54W" H 5250 3650 44  0000 L CNN
F 2 "Diodes_SMD:D_1206" V 5400 3550 50  0001 C CNN
F 3 "" V 5400 3550 50  0001 C CNN
	1    5400 3550
	-1   0    0    1   
$EndComp
NoConn ~ 8100 4050
Wire Wire Line
	8100 3850 8800 3850
$Comp
L R_Small R1
U 1 1 5A3835E7
P 8050 3200
F 0 "R1" H 8100 3250 50  0000 L CNN
F 1 "4k7" H 8100 3150 50  0000 L CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" H 8050 3200 50  0001 C CNN
F 3 "" H 8050 3200 50  0001 C CNN
	1    8050 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7900 3050 8050 3050
Wire Wire Line
	8050 3050 8150 3050
Connection ~ 8050 3050
Wire Wire Line
	4850 3550 5200 3550
Wire Wire Line
	5200 3550 5300 3550
Wire Wire Line
	5500 3550 5600 3550
Wire Wire Line
	5600 3550 5800 3550
Wire Wire Line
	5800 3550 6100 3550
Wire Wire Line
	8050 3350 8350 3350
Wire Wire Line
	8350 3350 8800 3350
Wire Wire Line
	8050 3350 8050 3300
Connection ~ 8350 3350
Wire Wire Line
	8800 3050 8550 3050
Wire Wire Line
	8050 3100 8050 3050
$Comp
L Fuse_Small F1
U 1 1 5A38D757
P 7800 3050
F 0 "F1" H 7800 2990 50  0000 C CNN
F 1 "3A" H 7800 3110 50  0000 C CNN
F 2 "SMD_Packages:SMD-1206_Pol" H 7800 3050 50  0001 C CNN
F 3 "" H 7800 3050 50  0001 C CNN
	1    7800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3050 7700 3050
Wire Wire Line
	8100 3950 8800 3950
Text Label 8800 3350 2    44   ~ 0
~PWRON
Text Label 8800 3750 2    44   ~ 0
LED
Wire Wire Line
	7600 3050 7600 3000
Wire Wire Line
	8100 3550 8800 3550
Wire Wire Line
	8100 3650 8800 3650
$Comp
L VCC #PWR016
U 1 1 5A79EF6A
P 5600 3400
F 0 "#PWR016" H 5600 3250 50  0001 C CNN
F 1 "VCC" H 5600 3550 50  0000 C CNN
F 2 "" H 5600 3400 50  0001 C CNN
F 3 "" H 5600 3400 50  0001 C CNN
	1    5600 3400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR017
U 1 1 5A79F05F
P 7100 5150
F 0 "#PWR017" H 7100 5000 50  0001 C CNN
F 1 "VCC" H 7100 5300 50  0000 C CNN
F 2 "" H 7100 5150 50  0001 C CNN
F 3 "" H 7100 5150 50  0001 C CNN
	1    7100 5150
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG018
U 1 1 5A79F091
P 7100 5400
F 0 "#FLG018" H 7100 5475 50  0001 C CNN
F 1 "PWR_FLAG" H 7100 5560 50  0000 C CNN
F 2 "" H 7100 5400 50  0001 C CNN
F 3 "" H 7100 5400 50  0001 C CNN
	1    7100 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 5400 7100 5150
Wire Wire Line
	6050 4250 6050 4050
Wire Wire Line
	6050 4050 6100 4050
Text Label 8800 3950 2    44   ~ 0
DELAY
$EndSCHEMATC
