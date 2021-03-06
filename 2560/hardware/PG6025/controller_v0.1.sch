EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Wifi Radio Board"
Date ""
Rev "Rubén Arce"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R1
U 1 1 5F92E027
P 1200 1700
F 0 "R1" H 1270 1746 50  0000 L CNN
F 1 "1k" H 1270 1655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1130 1700 50  0001 C CNN
F 3 "~" H 1200 1700 50  0001 C CNN
	1    1200 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5F92F47F
P 1200 2400
F 0 "#PWR0101" H 1200 2150 50  0001 C CNN
F 1 "GND" H 1205 2227 50  0000 C CNN
F 2 "" H 1200 2400 50  0001 C CNN
F 3 "" H 1200 2400 50  0001 C CNN
	1    1200 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2300 1200 2400
Wire Wire Line
	1200 2000 1200 1900
$Comp
L power:+3.3V #PWR0102
U 1 1 5F9304B9
P 1200 1350
F 0 "#PWR0102" H 1200 1200 50  0001 C CNN
F 1 "+3.3V" H 1215 1523 50  0000 C CNN
F 2 "" H 1200 1350 50  0001 C CNN
F 3 "" H 1200 1350 50  0001 C CNN
	1    1200 1350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0103
U 1 1 5F93109F
P 2400 700
F 0 "#PWR0103" H 2400 550 50  0001 C CNN
F 1 "+3.3V" H 2415 873 50  0000 C CNN
F 2 "" H 2400 700 50  0001 C CNN
F 3 "" H 2400 700 50  0001 C CNN
	1    2400 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 700  2400 800 
Wire Wire Line
	1200 1900 1400 1900
Connection ~ 1200 1900
Wire Wire Line
	1200 1900 1200 1850
Text GLabel 1600 1000 0    50   Input ~ 0
ENABLE
$Comp
L power:GND #PWR0104
U 1 1 5F932F5A
P 2400 3600
F 0 "#PWR0104" H 2400 3350 50  0001 C CNN
F 1 "GND" H 2405 3427 50  0000 C CNN
F 2 "" H 2400 3600 50  0001 C CNN
F 3 "" H 2400 3600 50  0001 C CNN
	1    2400 3600
	1    0    0    -1  
$EndComp
Text GLabel 1400 1900 2    50   Input ~ 0
ENABLE
Text GLabel 3100 1000 2    50   Input ~ 0
GPI0
Text GLabel 3100 1100 2    50   Input ~ 0
TX
Text GLabel 3100 1200 2    50   Input ~ 0
LED_STATUS
Text GLabel 3100 1300 2    50   Input ~ 0
RX
Text GLabel 3100 3200 2    50   Input ~ 0
BUTTON_RESET
Text GLabel 3100 1400 2    50   Input ~ 0
LED_WIFI
NoConn ~ 1800 1200
NoConn ~ 1800 1300
NoConn ~ 1800 2200
NoConn ~ 1800 2300
NoConn ~ 1800 2400
NoConn ~ 1800 2500
NoConn ~ 1800 2600
NoConn ~ 1800 2700
$Comp
L Device:R R2
U 1 1 5F935215
P 9600 1050
F 0 "R2" V 9393 1050 50  0000 C CNN
F 1 "1k" V 9484 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9530 1050 50  0001 C CNN
F 3 "~" H 9600 1050 50  0001 C CNN
	1    9600 1050
	0    1    1    0   
$EndComp
Text GLabel 9350 1050 0    50   Input ~ 0
LED_WIFI
$Comp
L Device:LED WIF1
U 1 1 5F93635D
P 10000 1050
F 0 "WIF1" H 9993 795 50  0000 C CNN
F 1 "LED" H 9993 886 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 10000 1050 50  0001 C CNN
F 3 "~" H 10000 1050 50  0001 C CNN
	1    10000 1050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5F936E83
P 10250 1050
F 0 "#PWR0105" H 10250 800 50  0001 C CNN
F 1 "GND" V 10255 922 50  0000 R CNN
F 2 "" H 10250 1050 50  0001 C CNN
F 3 "" H 10250 1050 50  0001 C CNN
	1    10250 1050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9350 1050 9450 1050
Wire Wire Line
	9750 1050 9850 1050
Wire Wire Line
	10150 1050 10250 1050
$Comp
L Device:R R3
U 1 1 5F938EBE
P 9600 1400
F 0 "R3" V 9393 1400 50  0000 C CNN
F 1 "1k" V 9484 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9530 1400 50  0001 C CNN
F 3 "~" H 9600 1400 50  0001 C CNN
	1    9600 1400
	0    1    1    0   
$EndComp
Text GLabel 9350 1400 0    50   Input ~ 0
LED_STATUS
$Comp
L Device:LED STAT1
U 1 1 5F938EC5
P 10000 1400
F 0 "STAT1" H 9993 1145 50  0000 C CNN
F 1 "STATUS" H 9993 1236 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 10000 1400 50  0001 C CNN
F 3 "~" H 10000 1400 50  0001 C CNN
	1    10000 1400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5F938ECB
P 10250 1400
F 0 "#PWR0106" H 10250 1150 50  0001 C CNN
F 1 "GND" V 10255 1272 50  0000 R CNN
F 2 "" H 10250 1400 50  0001 C CNN
F 3 "" H 10250 1400 50  0001 C CNN
	1    10250 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9350 1400 9450 1400
Wire Wire Line
	9750 1400 9850 1400
Wire Wire Line
	10150 1400 10250 1400
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 5F945760
P 6400 2150
F 0 "U1" H 6400 2392 50  0000 C CNN
F 1 "AMS1117-3.3" H 6400 2301 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6400 2350 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 6500 1900 50  0001 C CNN
	1    6400 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5F94ABE2
P 10100 2800
F 0 "C6" H 10215 2846 50  0000 L CNN
F 1 "1u" H 10215 2755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10138 2650 50  0001 C CNN
F 3 "~" H 10100 2800 50  0001 C CNN
	1    10100 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F94ABE8
P 10100 2350
F 0 "R4" H 10170 2396 50  0000 L CNN
F 1 "100k" H 10170 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10030 2350 50  0001 C CNN
F 3 "~" H 10100 2350 50  0001 C CNN
	1    10100 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5F94ABEE
P 10100 3050
F 0 "#PWR0107" H 10100 2800 50  0001 C CNN
F 1 "GND" H 10105 2877 50  0000 C CNN
F 2 "" H 10100 3050 50  0001 C CNN
F 3 "" H 10100 3050 50  0001 C CNN
	1    10100 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2950 10100 3050
$Comp
L power:+3.3V #PWR0108
U 1 1 5F94ABF6
P 10100 2200
F 0 "#PWR0108" H 10100 2050 50  0001 C CNN
F 1 "+3.3V" H 10115 2373 50  0000 C CNN
F 2 "" H 10100 2200 50  0001 C CNN
F 3 "" H 10100 2200 50  0001 C CNN
	1    10100 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2500 10100 2600
Wire Wire Line
	9850 2600 10100 2600
Connection ~ 10100 2600
Wire Wire Line
	10100 2600 10100 2650
$Comp
L Device:CP C3
U 1 1 5F9592E1
P 5900 2350
F 0 "C3" H 6018 2396 50  0000 L CNN
F 1 "10u" H 6018 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 5938 2200 50  0001 C CNN
F 3 "~" H 5900 2350 50  0001 C CNN
	1    5900 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 5F95A220
P 6850 2350
F 0 "C4" H 6968 2396 50  0000 L CNN
F 1 "10u" H 6968 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6888 2200 50  0001 C CNN
F 3 "~" H 6850 2350 50  0001 C CNN
	1    6850 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0111
U 1 1 5F95A778
P 1200 3000
F 0 "#PWR0111" H 1200 2850 50  0001 C CNN
F 1 "+3.3V" H 1215 3173 50  0000 C CNN
F 2 "" H 1200 3000 50  0001 C CNN
F 3 "" H 1200 3000 50  0001 C CNN
	1    1200 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5F95AD46
P 1200 3200
F 0 "C2" H 1315 3246 50  0000 L CNN
F 1 "10u" H 1315 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1238 3050 50  0001 C CNN
F 3 "~" H 1200 3200 50  0001 C CNN
	1    1200 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5F95B2A4
P 1200 3400
F 0 "#PWR0112" H 1200 3150 50  0001 C CNN
F 1 "GND" H 1205 3227 50  0000 C CNN
F 2 "" H 1200 3400 50  0001 C CNN
F 3 "" H 1200 3400 50  0001 C CNN
	1    1200 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 3400 1200 3350
Wire Wire Line
	1200 3050 1200 3000
$Comp
L Device:C C5
U 1 1 5F95BE5A
P 7250 2350
F 0 "C5" H 7365 2396 50  0000 L CNN
F 1 "10u" H 7365 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7288 2200 50  0001 C CNN
F 3 "~" H 7250 2350 50  0001 C CNN
	1    7250 2350
	1    0    0    -1  
$EndComp
Text Notes 6800 2850 0    50   ~ 0
Tantalum cap and low esr: \n0.3Ω - 22Ω
Wire Wire Line
	5900 2500 5900 2550
Wire Wire Line
	5900 2550 6400 2550
Wire Wire Line
	6400 2550 6400 2600
Wire Wire Line
	6400 2450 6400 2550
Connection ~ 6400 2550
Wire Wire Line
	6850 2500 6850 2550
Wire Wire Line
	6850 2550 6400 2550
Wire Wire Line
	7250 2500 7250 2550
Wire Wire Line
	7250 2550 6850 2550
Connection ~ 6850 2550
Wire Wire Line
	6850 2200 6850 2150
Wire Wire Line
	6850 2150 6700 2150
Wire Wire Line
	6850 2150 7250 2150
Wire Wire Line
	7250 2150 7250 2200
Connection ~ 6850 2150
Wire Wire Line
	5900 2200 5900 2150
Wire Wire Line
	5900 2150 6100 2150
$Comp
L power:+3.3V #PWR0114
U 1 1 5F9638C0
P 7600 2150
F 0 "#PWR0114" H 7600 2000 50  0001 C CNN
F 1 "+3.3V" H 7615 2323 50  0000 C CNN
F 2 "" H 7600 2150 50  0001 C CNN
F 3 "" H 7600 2150 50  0001 C CNN
	1    7600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2150 7600 2150
Connection ~ 7250 2150
$Comp
L power:GND #PWR0116
U 1 1 5F95E1BB
P 6400 2600
F 0 "#PWR0116" H 6400 2350 50  0001 C CNN
F 1 "GND" H 6405 2427 50  0000 C CNN
F 2 "" H 6400 2600 50  0001 C CNN
F 3 "" H 6400 2600 50  0001 C CNN
	1    6400 2600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 5F9E3DB5
P 950 2200
F 0 "SW3" V 950 2000 50  0000 L CNN
F 1 "SW_Push" V 1050 1850 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS810" H 950 2400 50  0001 C CNN
F 3 "~" H 950 2400 50  0001 C CNN
	1    950  2200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5F9E3DBB
P 950 2400
F 0 "#PWR0122" H 950 2150 50  0001 C CNN
F 1 "GND" H 955 2227 50  0000 C CNN
F 2 "" H 950 2400 50  0001 C CNN
F 3 "" H 950 2400 50  0001 C CNN
	1    950  2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1000 1800 1000
Text GLabel 3100 1500 2    50   Input ~ 0
CS
Wire Wire Line
	3000 1000 3100 1000
Wire Wire Line
	3100 1100 3000 1100
Wire Wire Line
	3000 1200 3100 1200
Wire Wire Line
	3100 1300 3000 1300
Wire Wire Line
	3000 1400 3100 1400
Wire Wire Line
	3100 1500 3000 1500
Wire Wire Line
	3000 3200 3100 3200
NoConn ~ 3000 1600
NoConn ~ 3000 3300
$Comp
L Diode_Bridge:MB6S D3
U 1 1 6030B129
P 5300 1100
F 0 "D3" H 5500 800 50  0000 L CNN
F 1 "MB6S" H 5500 900 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-269AA" H 5450 1225 50  0001 L CNN
F 3 "http://www.vishay.com/docs/88573/dfs.pdf" H 5300 1100 50  0001 C CNN
	1    5300 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR0124
U 1 1 603443BE
P 5300 1400
F 0 "#PWR0124" H 5300 1250 50  0001 C CNN
F 1 "+24V" H 5315 1573 50  0000 C CNN
F 2 "" H 5300 1400 50  0001 C CNN
F 3 "" H 5300 1400 50  0001 C CNN
	1    5300 1400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 6034959A
P 5000 1250
F 0 "#PWR0127" H 5000 1000 50  0001 C CNN
F 1 "GND" H 5005 1077 50  0000 C CNN
F 2 "" H 5000 1250 50  0001 C CNN
F 3 "" H 5000 1250 50  0001 C CNN
	1    5000 1250
	1    0    0    -1  
$EndComp
$Comp
L power:VDC #PWR0128
U 1 1 6034A17C
P 5650 950
F 0 "#PWR0128" H 5650 850 50  0001 C CNN
F 1 "VDC" H 5665 1123 50  0000 C CNN
F 2 "" H 5650 950 50  0001 C CNN
F 3 "" H 5650 950 50  0001 C CNN
	1    5650 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C7
U 1 1 6034ACD5
P 5950 1300
F 0 "C7" H 6068 1346 50  0000 L CNN
F 1 "470u" H 6068 1255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D12.5mm_P5.00mm" H 5988 1150 50  0001 C CNN
F 3 "~" H 5950 1300 50  0001 C CNN
	1    5950 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 60352D75
P 5950 1450
F 0 "#PWR0130" H 5950 1200 50  0001 C CNN
F 1 "GND" H 5955 1277 50  0000 C CNN
F 2 "" H 5950 1450 50  0001 C CNN
F 3 "" H 5950 1450 50  0001 C CNN
	1    5950 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0135
U 1 1 604330FF
P 5900 2150
F 0 "#PWR0135" H 5900 2000 50  0001 C CNN
F 1 "+5V" H 5915 2323 50  0000 C CNN
F 2 "" H 5900 2150 50  0001 C CNN
F 3 "" H 5900 2150 50  0001 C CNN
	1    5900 2150
	1    0    0    -1  
$EndComp
Connection ~ 5900 2150
$Comp
L power:+5V #PWR0136
U 1 1 604578A0
P 9500 1800
F 0 "#PWR0136" H 9500 1650 50  0001 C CNN
F 1 "+5V" V 9515 1928 50  0000 L CNN
F 2 "" H 9500 1800 50  0001 C CNN
F 3 "" H 9500 1800 50  0001 C CNN
	1    9500 1800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R7
U 1 1 60458648
P 9650 1800
F 0 "R7" V 9443 1800 50  0000 C CNN
F 1 "1k" V 9534 1800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9580 1800 50  0001 C CNN
F 3 "~" H 9650 1800 50  0001 C CNN
	1    9650 1800
	0    1    1    0   
$EndComp
$Comp
L Device:LED STAT2
U 1 1 60458925
P 9950 1800
F 0 "STAT2" H 9943 1545 50  0000 C CNN
F 1 "STATUS" H 9943 1636 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 9950 1800 50  0001 C CNN
F 3 "~" H 9950 1800 50  0001 C CNN
	1    9950 1800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0137
U 1 1 60458F94
P 10100 1800
F 0 "#PWR0137" H 10100 1550 50  0001 C CNN
F 1 "GND" V 10105 1672 50  0000 R CNN
F 2 "" H 10100 1800 50  0001 C CNN
F 3 "" H 10100 1800 50  0001 C CNN
	1    10100 1800
	0    -1   -1   0   
$EndComp
$Comp
L Regulator_Switching:LM2596S-5 U4
U 1 1 602E85CE
P 6900 1200
F 0 "U4" H 6900 1567 50  0000 C CNN
F 1 "LM2596S-5" H 6900 1476 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 6950 950 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 6900 1200 50  0001 C CNN
	1    6900 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 602F4D98
P 6900 1500
F 0 "#PWR0109" H 6900 1250 50  0001 C CNN
F 1 "GND" H 6905 1327 50  0000 C CNN
F 2 "" H 6900 1500 50  0001 C CNN
F 3 "" H 6900 1500 50  0001 C CNN
	1    6900 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 602F521D
P 6400 1300
F 0 "#PWR0115" H 6400 1050 50  0001 C CNN
F 1 "GND" H 6405 1127 50  0000 C CNN
F 2 "" H 6400 1300 50  0001 C CNN
F 3 "" H 6400 1300 50  0001 C CNN
	1    6400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1100 5650 1100
Wire Wire Line
	5650 1100 5650 950 
Wire Wire Line
	5950 1150 5950 1100
$Comp
L Diode:1N5820 D4
U 1 1 6032F0BD
P 7600 1500
F 0 "D4" V 7554 1580 50  0000 L CNN
F 1 "1N5820" V 7645 1580 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P15.24mm_Horizontal" H 7600 1325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88526/1n5820.pdf" H 7600 1500 50  0001 C CNN
	1    7600 1500
	0    1    1    0   
$EndComp
$Comp
L Device:L L1
U 1 1 6033039D
P 7900 1300
F 0 "L1" V 8090 1300 50  0000 C CNN
F 1 "33u 3A" V 7999 1300 50  0000 C CNN
F 2 "Inductor_SMD:L_6.3x6.3_H3" H 7900 1300 50  0001 C CNN
F 3 "~" H 7900 1300 50  0001 C CNN
	1    7900 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7400 1300 7600 1300
Wire Wire Line
	7600 1350 7600 1300
Connection ~ 7600 1300
Wire Wire Line
	7600 1300 7750 1300
Wire Wire Line
	8050 1300 8200 1300
Wire Wire Line
	8200 1300 8200 1350
$Comp
L power:+5V #PWR0118
U 1 1 60349D46
P 8200 1300
F 0 "#PWR0118" H 8200 1150 50  0001 C CNN
F 1 "+5V" H 8215 1473 50  0000 C CNN
F 2 "" H 8200 1300 50  0001 C CNN
F 3 "" H 8200 1300 50  0001 C CNN
	1    8200 1300
	1    0    0    -1  
$EndComp
Connection ~ 8200 1300
$Comp
L power:GND #PWR0120
U 1 1 6034A476
P 7600 1650
F 0 "#PWR0120" H 7600 1400 50  0001 C CNN
F 1 "GND" H 7605 1477 50  0000 C CNN
F 2 "" H 7600 1650 50  0001 C CNN
F 3 "" H 7600 1650 50  0001 C CNN
	1    7600 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 6034A740
P 8200 1650
F 0 "#PWR0123" H 8200 1400 50  0001 C CNN
F 1 "GND" H 8205 1477 50  0000 C CNN
F 2 "" H 8200 1650 50  0001 C CNN
F 3 "" H 8200 1650 50  0001 C CNN
	1    8200 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0126
U 1 1 6034AAC0
P 7400 1100
F 0 "#PWR0126" H 7400 950 50  0001 C CNN
F 1 "+5V" H 7415 1273 50  0000 C CNN
F 2 "" H 7400 1100 50  0001 C CNN
F 3 "" H 7400 1100 50  0001 C CNN
	1    7400 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 1100 5950 1100
Connection ~ 5650 1100
$Comp
L Device:C C1
U 1 1 5F92D1DA
P 1200 2150
F 0 "C1" H 1315 2196 50  0000 L CNN
F 1 "10u" H 1315 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1238 2000 50  0001 C CNN
F 3 "~" H 1200 2150 50  0001 C CNN
	1    1200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  2000 950  1900
Wire Wire Line
	950  1900 1200 1900
Wire Wire Line
	1200 1350 1200 1550
Wire Wire Line
	5000 1250 5000 1100
$Comp
L power:-24V #PWR0131
U 1 1 6026D39F
P 1250 4400
F 0 "#PWR0131" H 1250 4500 50  0001 C CNN
F 1 "-24V" H 1265 4573 50  0000 C CNN
F 2 "" H 1250 4400 50  0001 C CNN
F 3 "" H 1250 4400 50  0001 C CNN
	1    1250 4400
	-1   0    0    1   
$EndComp
$Comp
L power:+24V #PWR0132
U 1 1 602721B4
P 1250 4100
F 0 "#PWR0132" H 1250 3950 50  0001 C CNN
F 1 "+24V" H 1265 4273 50  0000 C CNN
F 2 "" H 1250 4100 50  0001 C CNN
F 3 "" H 1250 4100 50  0001 C CNN
	1    1250 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 603B1386
P 1450 4100
F 0 "J1" H 1530 4092 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 1600 3950 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 1450 4100 50  0001 C CNN
F 3 "~" H 1450 4100 50  0001 C CNN
	1    1450 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C9
U 1 1 60330B32
P 8200 1500
F 0 "C9" H 8318 1546 50  0000 L CNN
F 1 "330u 35V" H 8318 1455 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.4" H 8238 1350 50  0001 C CNN
F 3 "~" H 8200 1500 50  0001 C CNN
	1    8200 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1100 6400 1100
Connection ~ 5950 1100
Text GLabel 1850 4350 3    50   Input ~ 0
COM
Text GLabel 1950 4350 3    50   Input ~ 0
MV
Text GLabel 2050 4350 3    50   Input ~ 0
V1
Text GLabel 2150 4350 3    50   Input ~ 0
V2
Text GLabel 2250 4350 3    50   Input ~ 0
V3
Text GLabel 2350 4350 3    50   Input ~ 0
V4
Text GLabel 2450 4350 3    50   Input ~ 0
V5
Text GLabel 2550 4350 3    50   Input ~ 0
V6
Text GLabel 2650 4350 3    50   Input ~ 0
V7
Text GLabel 2750 4350 3    50   Input ~ 0
V8
Text GLabel 2850 4350 3    50   Input ~ 0
V9
Text GLabel 2950 4350 3    50   Input ~ 0
V10
Text GLabel 3050 4350 3    50   Input ~ 0
V11
Text GLabel 3150 4350 3    50   Input ~ 0
V12
Text GLabel 3250 4350 3    50   Input ~ 0
V13
Text GLabel 3350 4350 3    50   Input ~ 0
V14
Text GLabel 6100 3950 2    50   Input ~ 0
V1
Text GLabel 6100 5000 2    50   Input ~ 0
V2
Text GLabel 6300 5800 2    50   Input ~ 0
V3
$Comp
L power:+24V #PWR0110
U 1 1 603F68F9
P 6100 3550
F 0 "#PWR0110" H 6100 3400 50  0001 C CNN
F 1 "+24V" H 6115 3723 50  0000 C CNN
F 2 "" H 6100 3550 50  0001 C CNN
F 3 "" H 6100 3550 50  0001 C CNN
	1    6100 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 603F6F20
P 5600 3700
F 0 "R6" V 5393 3700 50  0000 C CNN
F 1 "100" V 5484 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5530 3700 50  0001 C CNN
F 3 "~" H 5600 3700 50  0001 C CNN
	1    5600 3700
	0    1    1    0   
$EndComp
Text GLabel 3000 1700 2    50   Input ~ 0
OUTPUT_1
Text GLabel 3000 1800 2    50   Input ~ 0
OUTPUT_2
Text GLabel 3000 1900 2    50   Input ~ 0
OUTPUT_3
Text GLabel 3000 2000 2    50   Input ~ 0
OUTPUT_4
Text GLabel 3000 2100 2    50   Input ~ 0
OUTPUT_5
Text GLabel 3000 2600 2    50   Input ~ 0
MOSI
Text GLabel 5350 3450 0    50   Input ~ 0
OUTPUT_1
Text GLabel 5400 4550 0    50   Input ~ 0
OUTPUT_2
Text GLabel 5400 5600 0    50   Input ~ 0
OUTPUT_3
Text GLabel 7250 4450 0    50   Input ~ 0
OUTPUT_5
$Comp
L power:+24V #PWR0119
U 1 1 604054C4
P 6100 4700
F 0 "#PWR0119" H 6100 4550 50  0001 C CNN
F 1 "+24V" H 6115 4873 50  0000 C CNN
F 2 "" H 6100 4700 50  0001 C CNN
F 3 "" H 6100 4700 50  0001 C CNN
	1    6100 4700
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:MOC3063M U6
U 1 1 6040A606
P 6000 5700
F 0 "U6" H 6000 6025 50  0000 C CNN
F 1 "MOC3063M" H 6000 5934 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm_LongPads" H 5800 5500 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/MO/MOC3061M.pdf" H 6000 5700 50  0001 L CNN
	1    6000 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 6040A612
P 5700 5800
F 0 "#PWR0129" H 5700 5550 50  0001 C CNN
F 1 "GND" H 5705 5627 50  0000 C CNN
F 2 "" H 5700 5800 50  0001 C CNN
F 3 "" H 5700 5800 50  0001 C CNN
	1    5700 5800
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR0133
U 1 1 60412370
P 6300 5600
F 0 "#PWR0133" H 6300 5450 50  0001 C CNN
F 1 "+24V" H 6315 5773 50  0000 C CNN
F 2 "" H 6300 5600 50  0001 C CNN
F 3 "" H 6300 5600 50  0001 C CNN
	1    6300 5600
	1    0    0    -1  
$EndComp
Text GLabel 3000 2400 2    50   Input ~ 0
SDA
Text GLabel 3000 2500 2    50   Input ~ 0
SCL
$Comp
L Connector:Conn_01x04_Female J4
U 1 1 60417445
P 9450 4050
F 0 "J4" H 9478 4026 50  0000 L CNN
F 1 "Conn_01x04_Female" H 9478 3935 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9450 4050 50  0001 C CNN
F 3 "~" H 9450 4050 50  0001 C CNN
	1    9450 4050
	1    0    0    -1  
$EndComp
Text GLabel 9250 4050 0    50   Input ~ 0
SDA
Text GLabel 9250 4150 0    50   Input ~ 0
SCL
$Comp
L power:GND #PWR0134
U 1 1 604179EB
P 9250 4250
F 0 "#PWR0134" H 9250 4000 50  0001 C CNN
F 1 "GND" H 9255 4077 50  0000 C CNN
F 2 "" H 9250 4250 50  0001 C CNN
F 3 "" H 9250 4250 50  0001 C CNN
	1    9250 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0138
U 1 1 60417E04
P 9250 3950
F 0 "#PWR0138" H 9250 3800 50  0001 C CNN
F 1 "+5V" H 9265 4123 50  0000 C CNN
F 2 "" H 9250 3950 50  0001 C CNN
F 3 "" H 9250 3950 50  0001 C CNN
	1    9250 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 6041D35E
P 5800 4950
F 0 "R9" V 5593 4950 50  0000 C CNN
F 1 "100" V 5684 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5730 4950 50  0001 C CNN
F 3 "~" H 5800 4950 50  0001 C CNN
	1    5800 4950
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 6041D70A
P 5550 5600
F 0 "R10" V 5343 5600 50  0000 C CNN
F 1 "100" V 5434 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5480 5600 50  0001 C CNN
F 3 "~" H 5550 5600 50  0001 C CNN
	1    5550 5600
	0    1    1    0   
$EndComp
$Comp
L Relay_SolidState:MOC3022M U8
U 1 1 6041DD4C
P 7850 4250
F 0 "U8" H 7850 4575 50  0000 C CNN
F 1 "MOC3022M" H 7850 4484 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm_LongPads" H 7650 4050 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/MO/MOC3020M.pdf" H 7850 4250 50  0001 L CNN
	1    7850 4250
	1    0    0    -1  
$EndComp
Text GLabel 8150 4350 2    50   Input ~ 0
V5
$Comp
L power:+24V #PWR0139
U 1 1 6041F92C
P 8150 4150
F 0 "#PWR0139" H 8150 4000 50  0001 C CNN
F 1 "+24V" H 8165 4323 50  0000 C CNN
F 2 "" H 8150 4150 50  0001 C CNN
F 3 "" H 8150 4150 50  0001 C CNN
	1    8150 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0140
U 1 1 6041FD3F
P 7550 4350
F 0 "#PWR0140" H 7550 4100 50  0001 C CNN
F 1 "GND" H 7555 4177 50  0000 C CNN
F 2 "" H 7550 4350 50  0001 C CNN
F 3 "" H 7550 4350 50  0001 C CNN
	1    7550 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 60422641
P 7400 4150
F 0 "R12" V 7193 4150 50  0000 C CNN
F 1 "100" V 7284 4150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7330 4150 50  0001 C CNN
F 3 "~" H 7400 4150 50  0001 C CNN
	1    7400 4150
	0    1    1    0   
$EndComp
Text GLabel 7250 3450 0    50   Input ~ 0
OUTPUT_4
$Comp
L Device:R R11
U 1 1 6041D9FA
P 7400 3450
F 0 "R11" V 7193 3450 50  0000 C CNN
F 1 "100" V 7284 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7330 3450 50  0001 C CNN
F 3 "~" H 7400 3450 50  0001 C CNN
	1    7400 3450
	0    1    1    0   
$EndComp
$Comp
L power:+24V #PWR0141
U 1 1 6041287E
P 8150 3450
F 0 "#PWR0141" H 8150 3300 50  0001 C CNN
F 1 "+24V" H 8165 3623 50  0000 C CNN
F 2 "" H 8150 3450 50  0001 C CNN
F 3 "" H 8150 3450 50  0001 C CNN
	1    8150 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0142
U 1 1 6040C98A
P 7550 3650
F 0 "#PWR0142" H 7550 3400 50  0001 C CNN
F 1 "GND" H 7555 3477 50  0000 C CNN
F 2 "" H 7550 3650 50  0001 C CNN
F 3 "" H 7550 3650 50  0001 C CNN
	1    7550 3650
	1    0    0    -1  
$EndComp
$Comp
L Relay_SolidState:MOC3063M U7
U 1 1 6040C97E
P 7850 3550
F 0 "U7" H 7850 3875 50  0000 C CNN
F 1 "MOC3063M" H 7850 3784 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm_LongPads" H 7650 3350 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/MO/MOC3061M.pdf" H 7850 3550 50  0001 L CNN
	1    7850 3550
	1    0    0    -1  
$EndComp
Text GLabel 8150 3650 2    50   Input ~ 0
V4
$Comp
L Device:R R5
U 1 1 6045EF44
P 5600 3250
F 0 "R5" V 5393 3250 50  0000 C CNN
F 1 "1k" V 5484 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5530 3250 50  0001 C CNN
F 3 "~" H 5600 3250 50  0001 C CNN
	1    5600 3250
	0    1    1    0   
$EndComp
$Comp
L Device:LED WIF2
U 1 1 6045EF4A
P 6000 3250
F 0 "WIF2" H 5993 2995 50  0000 C CNN
F 1 "LED" H 5993 3086 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6000 3250 50  0001 C CNN
F 3 "~" H 6000 3250 50  0001 C CNN
	1    6000 3250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0143
U 1 1 6045EF50
P 6250 3250
F 0 "#PWR0143" H 6250 3000 50  0001 C CNN
F 1 "GND" V 6255 3122 50  0000 R CNN
F 2 "" H 6250 3250 50  0001 C CNN
F 3 "" H 6250 3250 50  0001 C CNN
	1    6250 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5750 3250 5850 3250
Wire Wire Line
	6150 3250 6250 3250
Wire Wire Line
	5350 3450 5450 3450
Wire Wire Line
	5450 3450 5450 3250
Wire Wire Line
	5450 3450 5450 3700
Connection ~ 5450 3450
$Comp
L Device:R R8
U 1 1 6046D837
P 5600 4350
F 0 "R8" V 5393 4350 50  0000 C CNN
F 1 "1k" V 5484 4350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5530 4350 50  0001 C CNN
F 3 "~" H 5600 4350 50  0001 C CNN
	1    5600 4350
	0    1    1    0   
$EndComp
$Comp
L Device:LED WIF3
U 1 1 6046D83D
P 6000 4350
F 0 "WIF3" H 5993 4095 50  0000 C CNN
F 1 "LED" H 5993 4186 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6000 4350 50  0001 C CNN
F 3 "~" H 6000 4350 50  0001 C CNN
	1    6000 4350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0144
U 1 1 6046D843
P 6250 4350
F 0 "#PWR0144" H 6250 4100 50  0001 C CNN
F 1 "GND" V 6255 4222 50  0000 R CNN
F 2 "" H 6250 4350 50  0001 C CNN
F 3 "" H 6250 4350 50  0001 C CNN
	1    6250 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5750 4350 5850 4350
Wire Wire Line
	6150 4350 6250 4350
Wire Wire Line
	5450 4350 5450 4550
Wire Wire Line
	5450 4550 5400 4550
Connection ~ 5450 4550
$Comp
L Device:R R13
U 1 1 60480FB1
P 7450 4800
F 0 "R13" V 7243 4800 50  0000 C CNN
F 1 "1k" V 7334 4800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7380 4800 50  0001 C CNN
F 3 "~" H 7450 4800 50  0001 C CNN
	1    7450 4800
	0    1    1    0   
$EndComp
$Comp
L Device:LED WIF4
U 1 1 60480FB7
P 7850 4800
F 0 "WIF4" H 7843 4545 50  0000 C CNN
F 1 "LED" H 7843 4636 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 7850 4800 50  0001 C CNN
F 3 "~" H 7850 4800 50  0001 C CNN
	1    7850 4800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0145
U 1 1 60480FBD
P 8100 4800
F 0 "#PWR0145" H 8100 4550 50  0001 C CNN
F 1 "GND" V 8105 4672 50  0000 R CNN
F 2 "" H 8100 4800 50  0001 C CNN
F 3 "" H 8100 4800 50  0001 C CNN
	1    8100 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 4800 7700 4800
Wire Wire Line
	8000 4800 8100 4800
Wire Wire Line
	7250 4800 7300 4800
Wire Wire Line
	7250 4150 7250 4800
Text GLabel 9850 2600 0    50   Input ~ 0
button_up
$Comp
L Switch:SW_Push B2
U 1 1 604C0B2A
P 10500 2850
F 0 "B2" V 10454 2998 50  0000 L CNN
F 1 "SW_Push" V 10545 2998 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_SPST_PTS810" H 10500 3050 50  0001 C CNN
F 3 "~" H 10500 3050 50  0001 C CNN
	1    10500 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	10100 2600 10500 2600
Wire Wire Line
	10500 2600 10500 2650
$Comp
L power:GND #PWR0121
U 1 1 5F970194
P 10500 3050
F 0 "#PWR0121" H 10500 2800 50  0001 C CNN
F 1 "GND" H 10505 2877 50  0000 C CNN
F 2 "" H 10500 3050 50  0001 C CNN
F 3 "" H 10500 3050 50  0001 C CNN
	1    10500 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 6050E185
P 1850 4150
F 0 "J2" H 1930 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 2000 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 1850 4150 50  0001 C CNN
F 3 "~" H 1850 4150 50  0001 C CNN
	1    1850 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 60510F21
P 2050 4150
F 0 "J5" H 2130 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 2200 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 2050 4150 50  0001 C CNN
F 3 "~" H 2050 4150 50  0001 C CNN
	1    2050 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 605113D1
P 2250 4150
F 0 "J6" H 2330 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 2400 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 2250 4150 50  0001 C CNN
F 3 "~" H 2250 4150 50  0001 C CNN
	1    2250 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 60511783
P 2450 4150
F 0 "J7" H 2530 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 2600 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 2450 4150 50  0001 C CNN
F 3 "~" H 2450 4150 50  0001 C CNN
	1    2450 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J8
U 1 1 60511C56
P 2650 4150
F 0 "J8" H 2730 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 2800 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 2650 4150 50  0001 C CNN
F 3 "~" H 2650 4150 50  0001 C CNN
	1    2650 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J9
U 1 1 60511F59
P 2850 4150
F 0 "J9" H 2930 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 3000 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 2850 4150 50  0001 C CNN
F 3 "~" H 2850 4150 50  0001 C CNN
	1    2850 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J10
U 1 1 605124F2
P 3050 4150
F 0 "J10" H 3130 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 3200 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 3050 4150 50  0001 C CNN
F 3 "~" H 3050 4150 50  0001 C CNN
	1    3050 4150
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J11
U 1 1 60512A41
P 3250 4150
F 0 "J11" H 3330 4142 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 3400 4000 50  0001 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 3250 4150 50  0001 C CNN
F 3 "~" H 3250 4150 50  0001 C CNN
	1    3250 4150
	0    -1   -1   0   
$EndComp
$Comp
L Triac_Thyristor:Z0109NN D1
U 1 1 602F473F
P 6100 3700
F 0 "D1" H 6229 3746 50  0000 L CNN
F 1 "Z0109NN" H 6229 3655 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 6850 3550 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/z01.pdf" H 6250 4000 50  0001 C CNN
	1    6100 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3950 6100 3850
Wire Wire Line
	5750 3700 5950 3700
Wire Wire Line
	5950 3700 5950 3800
Text Notes 600  7100 0    50   ~ 0
Z0109NN6AA4 -SOT-232\nhttps://www.mouser.es/ProductDetail/STMicroelectronics/Z0109NN6AA4/?qs=ZSypp649SOVcEJ6jCl0U3A%3D%3D
$Comp
L Triac_Thyristor:Z0107MN D2
U 1 1 6030B7D5
P 6100 4850
F 0 "D2" H 6228 4896 50  0000 L CNN
F 1 "Z0107MN" H 6228 4805 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 6850 4700 50  0001 C CNN
F 3 "http://www.st.com/resource/en/datasheet/z01.pdf" H 6250 5150 50  0001 C CNN
	1    6100 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 4950 5650 4950
Wire Wire Line
	5450 4550 5450 4950
Text Notes 600  7300 0    50   ~ 0
Z0107MA -SOT54 (TO-92)\nhttps://www.mouser.es/ProductDetail/WeEn-Semiconductors/Z0107MA412/?qs=LOCUfHb8d9tGZhEwzrG9mw%3D%3D
Wire Wire Line
	1250 4200 1250 4400
$Comp
L power:-24V #PWR0113
U 1 1 60320F9E
P 1350 5050
F 0 "#PWR0113" H 1350 5150 50  0001 C CNN
F 1 "-24V" H 1365 5223 50  0000 C CNN
F 2 "" H 1350 5050 50  0001 C CNN
F 3 "" H 1350 5050 50  0001 C CNN
	1    1350 5050
	-1   0    0    1   
$EndComp
Text GLabel 1750 5000 3    50   Input ~ 0
COM
$Comp
L Device:Fuse F1
U 1 1 603E5C43
P 1550 4950
F 0 "F1" V 1353 4950 50  0000 C CNN
F 1 "Fuse" V 1444 4950 50  0000 C CNN
F 2 "Fuse:Fuse_1206_3216Metric" V 1480 4950 50  0001 C CNN
F 3 "~" H 1550 4950 50  0001 C CNN
	1    1550 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	1350 5050 1350 4950
Wire Wire Line
	1350 4950 1400 4950
Wire Wire Line
	1700 4950 1750 4950
Wire Wire Line
	1750 4950 1750 5000
$Comp
L RF_Module:ESP32-WROOM-32 U2
U 1 1 5F92C181
P 2400 2200
F 0 "U2" H 2800 3550 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 1950 3550 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 2400 700 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 2100 2250 50  0001 C CNN
	1    2400 2200
	1    0    0    -1  
$EndComp
Text GLabel 3000 3000 2    50   Input ~ 0
rotatory_3
Text GLabel 3000 3100 2    50   Input ~ 0
rotatory_2
Text GLabel 3000 2900 2    50   Input ~ 0
rotatory_1
Text GLabel 4250 1400 0    50   Input ~ 0
ENABLE
Text GLabel 4250 1300 0    50   Input ~ 0
RX
$Comp
L power:GND #PWR0117
U 1 1 6040892F
P 4250 1100
F 0 "#PWR0117" H 4250 850 50  0001 C CNN
F 1 "GND" H 4255 927 50  0000 C CNN
F 2 "" H 4250 1100 50  0001 C CNN
F 3 "" H 4250 1100 50  0001 C CNN
	1    4250 1100
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x05_Male J12
U 1 1 60408935
P 4450 1300
F 0 "J12" H 4422 1232 50  0000 R CNN
F 1 "Conn_01x05_Male" H 4422 1323 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 4450 1300 50  0001 C CNN
F 3 "~" H 4450 1300 50  0001 C CNN
	1    4450 1300
	-1   0    0    1   
$EndComp
Text GLabel 4250 1200 0    50   Input ~ 0
TX
Text GLabel 4250 1500 0    50   Input ~ 0
GPI0
$Comp
L Connector:Conn_01x05_Male J13
U 1 1 60423F6F
P 9450 5500
F 0 "J13" H 9422 5432 50  0000 R CNN
F 1 "Conn_01x05_Male" H 9422 5523 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 9450 5500 50  0001 C CNN
F 3 "~" H 9450 5500 50  0001 C CNN
	1    9450 5500
	-1   0    0    1   
$EndComp
Text GLabel 9250 5300 0    50   Input ~ 0
rotatory_3
Text GLabel 9250 5400 0    50   Input ~ 0
rotatory_2
Text GLabel 9250 5500 0    50   Input ~ 0
rotatory_1
$Comp
L power:+5V #PWR0156
U 1 1 604295D3
P 9250 5700
F 0 "#PWR0156" H 9250 5550 50  0001 C CNN
F 1 "+5V" H 9265 5873 50  0000 C CNN
F 2 "" H 9250 5700 50  0001 C CNN
F 3 "" H 9250 5700 50  0001 C CNN
	1    9250 5700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0157
U 1 1 60457F9C
P 9250 5600
F 0 "#PWR0157" H 9250 5350 50  0001 C CNN
F 1 "GND" H 9255 5427 50  0000 C CNN
F 2 "" H 9250 5600 50  0001 C CNN
F 3 "" H 9250 5600 50  0001 C CNN
	1    9250 5600
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 604594DE
P 6200 6500
F 0 "H1" H 6300 6546 50  0000 L CNN
F 1 "MountingHole" H 6300 6455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 6200 6500 50  0001 C CNN
F 3 "~" H 6200 6500 50  0001 C CNN
	1    6200 6500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 6046566F
P 6200 7250
F 0 "H4" H 6300 7296 50  0000 L CNN
F 1 "MountingHole" H 6300 7205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 6200 7250 50  0001 C CNN
F 3 "~" H 6200 7250 50  0001 C CNN
	1    6200 7250
	1    0    0    -1  
$EndComp
$Comp
L power:-24V #PWR0125
U 1 1 604B4E0C
P 5300 800
F 0 "#PWR0125" H 5300 900 50  0001 C CNN
F 1 "-24V" H 5315 973 50  0000 C CNN
F 2 "" H 5300 800 50  0001 C CNN
F 3 "" H 5300 800 50  0001 C CNN
	1    5300 800 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J3
U 1 1 604E0246
P 9450 4800
F 0 "J3" H 9422 4732 50  0000 R CNN
F 1 "Conn_01x05_Male" H 9422 4823 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Horizontal" H 9450 4800 50  0001 C CNN
F 3 "~" H 9450 4800 50  0001 C CNN
	1    9450 4800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0155
U 1 1 604D8331
P 9250 5000
F 0 "#PWR0155" H 9250 4750 50  0001 C CNN
F 1 "GND" H 9255 4827 50  0000 C CNN
F 2 "" H 9250 5000 50  0001 C CNN
F 3 "" H 9250 5000 50  0001 C CNN
	1    9250 5000
	1    0    0    -1  
$EndComp
Text GLabel 3000 2200 2    50   Input ~ 0
CLK
Text GLabel 3000 2300 2    50   Input ~ 0
MISO
Text GLabel 9250 4700 0    50   Input ~ 0
MISO
Text GLabel 9250 4600 0    50   Input ~ 0
MOSI
Text GLabel 9250 4900 0    50   Input ~ 0
CS
Text GLabel 9250 4800 0    50   Input ~ 0
CLK
$EndSCHEMATC
