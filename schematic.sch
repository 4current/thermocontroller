EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5600 3450 5200 3450
Wire Wire Line
	5200 3450 5200 3750
Wire Wire Line
	6300 1950 6300 1700
Wire Wire Line
	4400 3950 4400 4150
NoConn ~ 4800 2950
NoConn ~ 4800 3050
NoConn ~ 4800 3150
NoConn ~ 4800 3250
Entry Wire Line
	6200 1600 6300 1700
Wire Wire Line
	5200 3750 4800 3750
Wire Wire Line
	5600 3550 4800 3550
Wire Wire Line
	5600 2850 4800 2850
Wire Wire Line
	4800 2750 5600 2750
Wire Wire Line
	5600 2650 4800 2650
Wire Wire Line
	5600 2550 4800 2550
$Comp
L Device:R_POT_US RV1
U 1 1 5FEDE4A8
P 3600 3750
F 0 "RV1" H 3532 3796 50  0000 R CNN
F 1 "5K" H 3532 3705 50  0000 R CNN
F 2 "" H 3600 3750 50  0001 C CNN
F 3 "~" H 3600 3750 50  0001 C CNN
	1    3600 3750
	1    0    0    -1  
$EndComp
Entry Wire Line
	4900 1600 5000 1700
Entry Wire Line
	4800 1850 4900 1950
Wire Wire Line
	4900 1950 4900 2100
Wire Wire Line
	4900 3650 4800 3650
Wire Wire Line
	5000 1700 5000 4150
Wire Wire Line
	4400 4150 5000 4150
Entry Wire Line
	3500 1850 3600 1950
Connection ~ 4400 4150
Wire Wire Line
	4000 3450 3900 3450
Wire Wire Line
	3900 3450 3900 4150
Wire Wire Line
	3900 4150 4400 4150
Wire Wire Line
	4400 2350 4400 2100
Wire Wire Line
	4400 2100 4900 2100
Connection ~ 4900 2100
Wire Wire Line
	4900 2100 4900 3650
$Comp
L Display_Character:WC1602A DS1
U 1 1 5FEAB6C6
P 4400 3150
F 0 "DS1" H 4400 2169 50  0000 C CNN
F 1 "WC1602A" H 4400 2260 50  0000 C CNN
F 2 "Display:WC1602A" H 4400 2250 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 5100 3150 50  0001 C CNN
	1    4400 3150
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 5FED89CE
P 3800 3350
F 0 "R1" V 4005 3350 50  0000 C CNN
F 1 "560" V 3914 3350 50  0000 C CNN
F 2 "" H 3800 3350 50  0001 C CNN
F 3 "~" H 3800 3350 50  0001 C CNN
	1    3800 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3600 1950 3600 3350
Wire Wire Line
	3750 3750 4000 3750
Wire Wire Line
	3900 3350 4000 3350
Wire Wire Line
	3700 3350 3600 3350
Connection ~ 3600 3350
Wire Wire Line
	3600 3350 3600 3600
Wire Wire Line
	3600 3900 3600 4150
Wire Wire Line
	3600 4150 3900 4150
Connection ~ 3900 4150
$Comp
L Sensor_Temperature:LM35-LP U?
U 1 1 5FF9E7B1
P 7250 2950
F 0 "U?" H 6920 2996 50  0000 R CNN
F 1 "LM35-LP" H 6920 2905 50  0000 R CNN
F 2 "" H 7300 2700 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm35.pdf" H 7250 2950 50  0001 C CNN
	1    7250 2950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6600 2950 6850 2950
Entry Wire Line
	7150 1600 7250 1700
Wire Wire Line
	7250 1700 7250 2650
Entry Wire Line
	7650 1850 7750 1950
Wire Wire Line
	7750 1950 7750 3500
Wire Wire Line
	7750 3500 7250 3500
Wire Wire Line
	7250 3500 7250 3250
Wire Wire Line
	5600 3150 5400 3150
$Comp
L Device:R_Small_US R?
U 1 1 5FFBD7CD
P 6750 4400
F 0 "R?" V 6955 4400 50  0000 C CNN
F 1 "R_Small_US" V 6864 4400 50  0000 C CNN
F 2 "" H 6750 4400 50  0001 C CNN
F 3 "~" H 6750 4400 50  0001 C CNN
	1    6750 4400
	0    -1   -1   0   
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v2.x A?
U 1 1 5FEA8AC6
P 6100 2950
F 0 "A?" H 6100 1861 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 6100 1770 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6100 2950 50  0001 C CIN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6100 2950 50  0001 C CNN
	1    6100 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4400 5600 4400
Wire Wire Line
	5600 3650 5600 4400
Wire Bus Line
	2850 1850 8050 1850
Wire Bus Line
	2850 1600 8050 1600
$EndSCHEMATC
