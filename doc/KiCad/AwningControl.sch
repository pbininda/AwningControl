EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
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
EELAYER 25 0
EELAYER END
$Descr User 8661 5118
encoding utf-8
Sheet 1 1
Title "Markisensteuerung"
Date "2018-03-25"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L SW_SPDT Switch0
U 1 1 5AB75345
P 1700 1150
F 0 "Switch0" H 1700 1320 50  0000 C CNN
F 1 "Hauptschalter" H 1550 950 50  0000 L CNN
F 2 "" H 1700 1150 50  0001 C CNN
F 3 "" H 1700 1150 50  0001 C CNN
	1    1700 1150
	1    0    0    -1  
$EndComp
$Comp
L SW_SPST Switch1
U 1 1 5AB7538D
P 3050 1250
F 0 "Switch1" H 3050 1375 50  0000 C CNN
F 1 "Markisenschalter" H 3050 1150 50  0000 C CNN
F 2 "" H 3050 1250 50  0001 C CNN
F 3 "" H 3050 1250 50  0001 C CNN
	1    3050 1250
	1    0    0    -1  
$EndComp
$Comp
L SW_SPST Switch2
U 1 1 5AB75504
P 3050 1700
F 0 "Switch2" H 3050 1825 50  0000 C CNN
F 1 "Markisenschalter" H 3050 1600 50  0000 C CNN
F 2 "" H 3050 1700 50  0001 C CNN
F 3 "" H 3050 1700 50  0001 C CNN
	1    3050 1700
	1    0    0    -1  
$EndComp
$Comp
L Motor_AC Motor1
U 1 1 5AB7554D
P 4400 1500
F 0 "Motor1" H 4500 1600 50  0000 L CNN
F 1 "Markisenmotor" H 4500 1300 50  0000 L TNN
F 2 "" H 4400 1410 50  0001 C CNN
F 3 "" H 4400 1410 50  0001 C CNN
	1    4400 1500
	1    0    0    -1  
$EndComp
$Comp
L Motor_AC Motor2
U 1 1 5AB75592
P 4500 2200
F 0 "Motor2" H 4600 2300 50  0000 L CNN
F 1 "Markisenmotor" H 4600 2000 50  0000 L TNN
F 2 "" H 4500 2110 50  0001 C CNN
F 3 "" H 4500 2110 50  0001 C CNN
	1    4500 2200
	1    0    0    -1  
$EndComp
$Comp
L FINDER-40.31 Relay1
U 1 1 5AB75F0C
P 6750 1500
F 0 "Relay1" H 7200 1650 50  0000 L CNN
F 1 "5V/220V Relay" H 7200 1550 50  0000 L CNN
F 2 "Relays_THT:Relay_SPDT_Finder_40.31" H 7890 1460 50  0001 C CNN
F 3 "" H 6750 1500 50  0001 C CNN
	1    6750 1500
	-1   0    0    1   
$EndComp
$Comp
L FINDER-40.31 Relay2
U 1 1 5AB75F57
P 6750 2300
F 0 "Relay2" H 7200 2450 50  0000 L CNN
F 1 "5V/220V Relay" H 7200 2350 50  0000 L CNN
F 2 "Relays_THT:Relay_SPDT_Finder_40.31" H 7890 2260 50  0001 C CNN
F 3 "" H 6750 2300 50  0001 C CNN
	1    6750 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	1900 1250 2700 1250
Wire Wire Line
	2700 1250 2850 1250
Wire Wire Line
	2700 1250 2700 1700
Wire Wire Line
	2700 1700 2850 1700
Connection ~ 2700 1250
Wire Wire Line
	3250 1250 4400 1250
Wire Wire Line
	4400 1250 5400 1250
Wire Wire Line
	4400 1250 4400 1300
Wire Wire Line
	3250 1700 4000 1700
Wire Wire Line
	4000 1700 4000 1950
Wire Wire Line
	4000 1950 4500 1950
Wire Wire Line
	4500 1950 5300 1950
Wire Wire Line
	1350 1550 1350 2600
Wire Wire Line
	1350 1550 950  1550
Wire Wire Line
	4400 1800 4400 1850
Wire Wire Line
	4400 1850 5200 1850
Wire Wire Line
	5200 2600 5200 1850
Wire Wire Line
	1350 2600 4500 2600
Wire Wire Line
	4500 2600 5200 2600
Wire Wire Line
	4500 1950 4500 2000
Wire Wire Line
	4500 2500 4500 2600
Connection ~ 4500 2600
Wire Wire Line
	1900 1050 6550 1050
Wire Wire Line
	6550 1050 7600 1050
Wire Wire Line
	6550 1050 6550 1200
Wire Wire Line
	7600 1050 7600 1900
Wire Wire Line
	7600 1900 6550 1900
Wire Wire Line
	6550 1900 6550 2000
Connection ~ 6550 1050
Wire Wire Line
	6450 1800 6450 1900
Wire Wire Line
	6450 1900 5400 1900
Wire Wire Line
	5400 1900 5400 1250
Connection ~ 4400 1250
Wire Wire Line
	6450 2600 6450 2750
Wire Wire Line
	6450 2750 5300 2750
Wire Wire Line
	5300 2750 5300 1950
Connection ~ 4500 1950
Wire Wire Line
	950  1350 1350 1350
Wire Wire Line
	1350 1350 1350 1150
Wire Wire Line
	1350 1150 1500 1150
$Comp
L VAC #PWR?
U 1 1 5AB7B601
P 950 1350
F 0 "#PWR?" H 950 1250 50  0001 C CNN
F 1 "VAC" H 950 1600 50  0000 C CNN
F 2 "" H 950 1350 50  0001 C CNN
F 3 "" H 950 1350 50  0001 C CNN
F 4 "220V" H 950 1300 60  0000 C CNN "Voltage"
	1    950  1350
	1    0    0    -1  
$EndComp
$Comp
L GNDREF #PWR?
U 1 1 5AB7B623
P 950 1550
F 0 "#PWR?" H 950 1300 50  0001 C CNN
F 1 "GNDREF" H 950 1400 50  0000 C CNN
F 2 "" H 950 1550 50  0001 C CNN
F 3 "" H 950 1550 50  0001 C CNN
	1    950  1550
	1    0    0    -1  
$EndComp
Text Label 2800 1050 0    31   ~ 0
220V_Phase_Braun
Text Label 3600 1250 0    31   ~ 0
220V_Phase_Braun
Text Label 3600 1700 0    31   ~ 0
220V_Phase_Schwarz
Text Label 4900 1250 0    31   ~ 0
220V_Phase_Braun
Text Label 5600 2750 0    31   ~ 0
220V_Phase_Schwarz
Text Label 3350 2600 0    31   ~ 0
Neutral_Blau
Text Label 7250 1050 0    31   ~ 0
220V_Phase_Braun
$EndSCHEMATC
