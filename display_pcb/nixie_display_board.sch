EESchema Schematic File Version 4
LIBS:nixie_display_board-cache
EELAYER 29 0
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
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U1
U 1 1 5D0C7463
P 1500 1600
F 0 "U1" H 1500 1842 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 1650 1750 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Vertical" H 1500 1800 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 1600 1350 50  0001 C CNN
	1    1500 1600
	1    0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5D0C8160
P 1650 1250
F 0 "C2" V 1765 1296 50  0000 L CNN
F 1 "C" V 1765 1205 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D6.0mm_W2.5mm_P5.00mm" H 1688 1100 50  0001 C CNN
F 3 "~" H 1650 1250 50  0001 C CNN
	1    1650 1250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C1
U 1 1 5D0C8613
P 1350 1250
F 0 "C1" V 1465 1296 50  0000 L CNN
F 1 "C" V 1465 1205 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D6.0mm_W2.5mm_P5.00mm" H 1388 1100 50  0001 C CNN
F 3 "~" H 1350 1250 50  0001 C CNN
	1    1350 1250
	0    -1   -1   0   
$EndComp
$Comp
L nixie_display_board:CS-CONNECTOR J3
U 1 1 5D0DD1F1
P 2900 4650
F 0 "J3" H 2272 4621 50  0000 R CNN
F 1 "CS-CONNECTOR" H 2272 4712 50  0000 R CNN
F 2 "nixie_display_board:cs-connector" H 2900 4650 50  0001 C CNN
F 3 "" H 2900 4650 50  0001 C CNN
	1    2900 4650
	1    0    0    1   
$EndComp
$Comp
L nixie_display_board:POWER-CONNECTOR J1
U 1 1 5D0DD794
P 900 950
F 0 "J1" V 1215 867 50  0000 C CNN
F 1 "POWER-CONNECTOR" V 1124 867 50  0000 C CNN
F 2 "nixie_display_board:power-connector" H 900 950 50  0001 C CNN
F 3 "" H 900 950 50  0001 C CNN
	1    900  950 
	0    -1   -1   0   
$EndComp
$Comp
L nixie_display_board:SCK-MOSI-CONNECTOR J2
U 1 1 5D0DDC93
P 1300 3700
F 0 "J2" V 985 3642 50  0000 C CNN
F 1 "SCK-MOSI-CONNECTOR" V 1076 3642 50  0000 C CNN
F 2 "nixie_display_board:sck-mosi-connector" H 1300 3700 50  0001 C CNN
F 3 "" H 1300 3700 50  0001 C CNN
	1    1300 3700
	0    -1   1    0   
$EndComp
$Comp
L nixie_display_board:HV-POWER-SUPPLY PS1
U 1 1 5D0DE0EE
P 1400 2650
F 0 "PS1" H 1073 2521 50  0000 R CNN
F 1 "HV-POWER-SUPPLY" H 1800 3100 50  0000 R CNN
F 2 "nixie_display_board:hv-power-supply" H 1400 2650 50  0001 C CNN
F 3 "" H 1400 2650 50  0001 C CNN
	1    1400 2650
	1    0    0    1   
$EndComp
Wire Wire Line
	1500 1300 1500 1250
Wire Wire Line
	1500 900  1200 900 
Connection ~ 1500 1250
Wire Wire Line
	1500 1250 1500 900 
Wire Wire Line
	1200 1000 1200 1250
Wire Wire Line
	1200 1250 1200 1600
Connection ~ 1200 1250
Wire Wire Line
	1800 1600 1800 1250
Wire Wire Line
	1200 1600 1200 2100
Connection ~ 1200 1600
Wire Wire Line
	1500 900  1900 900 
Wire Wire Line
	1900 900  1900 1900
Wire Wire Line
	1900 1900 1500 1900
Wire Wire Line
	1300 1900 1300 2100
Connection ~ 1500 900 
Wire Wire Line
	1500 2100 1500 1900
Connection ~ 1500 1900
Wire Wire Line
	1500 1900 1300 1900
$Comp
L nixie_display_board:EXIXE-12 EX1
U 1 1 5D0F9B10
P 2300 2800
F 0 "EX1" H 2728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 2050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 2200 2700 50  0001 C CNN
F 3 "" H 2200 2700 50  0001 C CNN
	1    2300 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2100 1600 2000
Wire Wire Line
	1600 2000 2000 2000
Wire Wire Line
	2000 2000 2000 2100
Wire Wire Line
	1900 900  2500 900 
Wire Wire Line
	2500 900  2500 2100
Connection ~ 1900 900 
Wire Wire Line
	1800 1250 2600 1250
Wire Wire Line
	2600 1250 2600 2100
Connection ~ 1800 1250
Wire Wire Line
	1600 3650 2100 3650
Wire Wire Line
	2100 3650 2100 3500
$Comp
L nixie_display_board:EXIXE-12 EX2
U 1 1 5D100234
P 3300 2800
F 0 "EX2" H 3728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 3050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 3200 2700 50  0001 C CNN
F 3 "" H 3200 2700 50  0001 C CNN
	1    3300 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3650 3100 3650
Wire Wire Line
	3100 3650 3100 3500
Connection ~ 2100 3650
Wire Wire Line
	2000 2000 3000 2000
Wire Wire Line
	3000 2000 3000 2100
Connection ~ 2000 2000
Wire Wire Line
	2600 1250 3600 1250
Wire Wire Line
	3600 1250 3600 2100
Connection ~ 2600 1250
Wire Wire Line
	2500 900  3500 900 
Wire Wire Line
	3500 900  3500 2100
Connection ~ 2500 900 
$Comp
L nixie_display_board:EXIXE-12 EX3
U 1 1 5D102C04
P 4300 2800
F 0 "EX3" H 4728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 4050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 4200 2700 50  0001 C CNN
F 3 "" H 4200 2700 50  0001 C CNN
	1    4300 2800
	1    0    0    -1  
$EndComp
$Comp
L nixie_display_board:EXIXE-12 EX4
U 1 1 5D10361A
P 5300 2800
F 0 "EX4" H 5728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 5050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 5200 2700 50  0001 C CNN
F 3 "" H 5200 2700 50  0001 C CNN
	1    5300 2800
	1    0    0    -1  
$EndComp
$Comp
L nixie_display_board:EXIXE-12 EX5
U 1 1 5D10455F
P 6300 2800
F 0 "EX5" H 6728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 6050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 6200 2700 50  0001 C CNN
F 3 "" H 6200 2700 50  0001 C CNN
	1    6300 2800
	1    0    0    -1  
$EndComp
$Comp
L nixie_display_board:EXIXE-12 EX6
U 1 1 5D104F6B
P 7300 2800
F 0 "EX6" H 7728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 7050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 7200 2700 50  0001 C CNN
F 3 "" H 7200 2700 50  0001 C CNN
	1    7300 2800
	1    0    0    -1  
$EndComp
$Comp
L nixie_display_board:EXIXE-12 EX7
U 1 1 5D1061D4
P 8300 2800
F 0 "EX7" H 8728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 8050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 8200 2700 50  0001 C CNN
F 3 "" H 8200 2700 50  0001 C CNN
	1    8300 2800
	1    0    0    -1  
$EndComp
$Comp
L nixie_display_board:EXIXE-12 EX8
U 1 1 5D106BB1
P 9300 2800
F 0 "EX8" H 9728 2846 50  0000 L CNN
F 1 "EXIXE-12" H 9050 3350 50  0000 L CNN
F 2 "nixie_display_board:exixe-12-board" H 9200 2700 50  0001 C CNN
F 3 "" H 9200 2700 50  0001 C CNN
	1    9300 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2000 4000 2000
Wire Wire Line
	4000 2000 4000 2100
Connection ~ 3000 2000
Wire Wire Line
	4000 2000 5000 2000
Wire Wire Line
	5000 2000 5000 2100
Connection ~ 4000 2000
Wire Wire Line
	5000 2000 6000 2000
Wire Wire Line
	6000 2000 6000 2100
Connection ~ 5000 2000
Wire Wire Line
	7000 2000 7000 2100
Connection ~ 6000 2000
Wire Wire Line
	8000 2000 8000 2100
Wire Wire Line
	6000 2000 7000 2000
Connection ~ 7000 2000
Wire Wire Line
	7000 2000 8000 2000
Wire Wire Line
	8000 2000 9000 2000
Wire Wire Line
	9000 2000 9000 2100
Connection ~ 8000 2000
Wire Wire Line
	3600 1250 4600 1250
Wire Wire Line
	4600 1250 4600 2100
Connection ~ 3600 1250
Wire Wire Line
	4600 1250 5600 1250
Wire Wire Line
	5600 1250 5600 2100
Connection ~ 4600 1250
Wire Wire Line
	5600 1250 6600 1250
Wire Wire Line
	6600 1250 6600 2100
Connection ~ 5600 1250
Wire Wire Line
	6600 1250 7600 1250
Wire Wire Line
	7600 1250 7600 2100
Connection ~ 6600 1250
Wire Wire Line
	7600 1250 8600 1250
Wire Wire Line
	8600 1250 8600 2100
Connection ~ 7600 1250
Wire Wire Line
	8600 1250 9600 1250
Wire Wire Line
	9600 1250 9600 2100
Connection ~ 8600 1250
Wire Wire Line
	3500 900  4500 900 
Wire Wire Line
	4500 900  4500 2100
Connection ~ 3500 900 
Wire Wire Line
	4500 900  5500 900 
Wire Wire Line
	5500 900  5500 2100
Connection ~ 4500 900 
Wire Wire Line
	5500 900  6500 900 
Wire Wire Line
	6500 900  6500 2100
Connection ~ 5500 900 
Wire Wire Line
	6500 900  7500 900 
Wire Wire Line
	7500 900  7500 2100
Connection ~ 6500 900 
Wire Wire Line
	7500 900  8500 900 
Wire Wire Line
	8500 900  8500 2100
Connection ~ 7500 900 
Wire Wire Line
	8500 900  9500 900 
Wire Wire Line
	9500 900  9500 2100
Connection ~ 8500 900 
Wire Wire Line
	3100 3650 4100 3650
Wire Wire Line
	4100 3650 4100 3500
Connection ~ 3100 3650
Wire Wire Line
	4100 3650 5100 3650
Wire Wire Line
	5100 3650 5100 3500
Connection ~ 4100 3650
Wire Wire Line
	5100 3650 6100 3650
Wire Wire Line
	6100 3650 6100 3500
Connection ~ 5100 3650
Wire Wire Line
	6100 3650 7100 3650
Wire Wire Line
	7100 3650 7100 3500
Connection ~ 6100 3650
Wire Wire Line
	7100 3650 8100 3650
Wire Wire Line
	8100 3650 8100 3500
Connection ~ 7100 3650
Wire Wire Line
	8100 3650 9100 3650
Wire Wire Line
	9100 3650 9100 3500
Connection ~ 8100 3650
Wire Wire Line
	2500 3850 3400 3850
Wire Wire Line
	3400 3850 3400 3500
Wire Wire Line
	2600 3950 4400 3950
Wire Wire Line
	4400 3950 4400 3500
Wire Wire Line
	2700 4050 5400 4050
Wire Wire Line
	5400 4050 5400 3500
Wire Wire Line
	2800 4150 6400 4150
Wire Wire Line
	6400 4150 6400 3500
Wire Wire Line
	2900 4250 7400 4250
Wire Wire Line
	7400 4250 7400 3500
Wire Wire Line
	3000 4350 8400 4350
Wire Wire Line
	8400 4350 8400 3500
Wire Wire Line
	3100 4450 9400 4450
Wire Wire Line
	9400 4450 9400 3500
Wire Wire Line
	2400 4450 2400 3500
Wire Wire Line
	2500 4450 2500 3850
Wire Wire Line
	2600 4450 2600 3950
Wire Wire Line
	2700 4450 2700 4050
Wire Wire Line
	2800 4450 2800 4150
Wire Wire Line
	2900 4450 2900 4250
Wire Wire Line
	3000 4450 3000 4350
Wire Wire Line
	1600 3750 2300 3750
Wire Wire Line
	2300 3500 2300 3750
Connection ~ 2300 3750
Wire Wire Line
	2300 3750 3300 3750
Wire Wire Line
	3300 3500 3300 3750
Connection ~ 3300 3750
Wire Wire Line
	3300 3750 4300 3750
Wire Wire Line
	4300 3500 4300 3750
Connection ~ 4300 3750
Wire Wire Line
	4300 3750 5300 3750
Wire Wire Line
	5300 3500 5300 3750
Connection ~ 5300 3750
Wire Wire Line
	5300 3750 6300 3750
Wire Wire Line
	6300 3500 6300 3750
Connection ~ 6300 3750
Wire Wire Line
	6300 3750 7300 3750
Wire Wire Line
	7300 3500 7300 3750
Connection ~ 7300 3750
Wire Wire Line
	7300 3750 8300 3750
Wire Wire Line
	8300 3500 8300 3750
Connection ~ 8300 3750
Wire Wire Line
	9300 3750 9300 3500
Wire Wire Line
	8300 3750 9300 3750
$EndSCHEMATC
