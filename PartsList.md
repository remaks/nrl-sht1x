# NRL-SHT1X Hardware Parts List #

This is a complete parts list for the hardware necessary to build a NRL-SHT1X temperature and relative humidity sensor system, which includes a T-RH Sensor Hub and SHT1X Sensor PCB. This list does not include in the printed circuit board (PCB), which must be obtained separating using the EAGLE schematic (.sch) and board (.brb) files. A copy of the parts list is included in the source code, but the most up-to-date listing is here.

The order number and supplier are only recommendations. Most parts can be purchased from any supplier or distributor.

## T-RH Sensor Hub ##

### Printed Circuit Board Components ###

| **Description** | **Qty** | **Part Number** | **Manufacturer** | **Order Number** | **Supplier** |
|:----------------|:--------|:----------------|:-----------------|:-----------------|:-------------|
| Arduino Microcontroller | 1	      | ATmega328P      | Atmel            | [DEV-10524](https://www.sparkfun.com/products/10524) | [Sparkfun](http://www.sparkfun.com) |
| RS-232 to TTL IC | 1       | MAX232CPE+      | Maxim            | [MAX232CPE+-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=MAX232CPE%2B-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| IC I2C Bus Extender 8-DIP | 3       | P82B715TD,112   | NXP Semiconductors | [568-1006-5-ND](http://www.digikey.com/product-search/en?x=0&y=0&lang=en&site=us&KeyWords=568-1006-5-ND) | [Digi-Key](http://www.digikey.com) |
| 9V to 5V voltage regulator | 1       | LM2940-5.0      | National Semiconductor | [LM2940IMP-5.0CT-ND](http://www.digikey.com/product-detail/en/LM2940IMP-5.0%2FNOPB/LM2940IMP-5.0TR-ND/270714) | [Digi-Key](http://www.digikey.com) |
| 10K Ohm Through Hole Trim Pot | 1       | 3296W-1-103LF   | Bourns Inc.      | [3296W-103LF-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=3296W-103LF-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 1 uF Through Hole Capacitor | 5       | C330C105K5R5TA  | Kemet            | [399-4389-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=399-4389-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 22 uF Through Hole Capacitor | 2       |	T350K226K035AT  | Kemet            | [399-3595-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=399-3595-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 0.47 uF Through Hole Capacitor | 2       | T350B474K050AT  | Kemet            | [399-3552-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=399-3552-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 20 pF Through Hole Capacitor | 2       | RPE5C2A200J2P1Z03B | Murata Electronics | [490-3703-ND](http://www.digikey.com/product-detail/en/RPE5C1H200J2P1Z03B/490-3703-ND/946339) | [Digi-Key](http://www.digikey.com) |
| 0.1 uF Through Hole Capacitor | 2       | C315C104M5U5TA  | Kemet            | [399-4151-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=399-4151-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 16 MHz Oscillator | 1       | ECS-160-20-4X   | ECS Inc          | [X1103-ND](http://www.digikey.com/product-detail/en/ECS-160-20-4X/X1103-ND/827594) | [Digi-Key](http://www.digikey.com) |
| LED SMD-1206    | 1       | CMDA1CG7A1Z     | Chicago Miniature Lighting | [L71504CT-ND](http://www.digikey.com/product-detail/en/CMDA1CG7A1Z/L71504TR-ND/408777) | [Digi-Key](http://www.digikey.com) |
| 10 Ohm Through Hole Resistor | 1       | CFR-25JB-10R    |	Yageo            | [10QBK-ND](http://www.digikey.com/product-detail/en/CFR-25JB-52-10R/10QBK-ND/340) | [Digi-Key](http://www.digikey.com) |
| 10K Ohm Through Hole Resistor | 7       | CFR-25JB-10K    | Yageo            | [10KQBK-ND](http://www.digikey.com/product-detail/en/CFR-25JB-52-10K/10KQBK-ND/338) | [Digi-Key](http://www.digikey.com) |
| 220 Ohm Through Hole Resistor | 1       | CFR-25JB-220R   | Yageo            | [220QBK-ND](http://www.digikey.com/product-detail/en/CFR-25JB-52-220R/220QBK-ND/1295) | [Digi-Key](http://www.digikey.com) |
| 28-pin DIP Socket | 1       | 1-390261-9      | TE Connectivity  | [A100210-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A100210-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 16-pin DIP Socket | 1       | 1-390261-4      | TE Connectivity  | [A100206-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A100206-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection header 2-position with friction lock | 1       | 22-27-2021      | Molex Connector Corporation | [WM4111-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=WM4111-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection header 3-position with friction lock | 3	      | 22-27-2031      | Molex Connector Corporation |	[WM4112-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=WM4112-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection header 4-position with friction lock | 1       | 22-27-2041      | Molex Connector Corporation | [WM4113-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=WM4113-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 36-position header pins | 1       | 68001-436HLF    | FCI              | [609-2224-ND](http://www.digikey.com/product-search/en?x=0&y=0&lang=en&site=us&KeyWords=609-2224-ND) | [Digi-Key](http://www.digikey.com) |

### Project Box Components ###

| **Description** | **Qty** | **Part Number** | **Manufacturer** | **Order Number** | **Supplier** |
|:----------------|:--------|:----------------|:-----------------|:-----------------|:-------------|
| White on Black LCD | 1       | GDM1602K        | Xiamen Ocular    | [LCD-00709](https://www.sparkfun.com/products/709?) | [Sparkfun](http://www.sparkfun.com) |
| DB9 Female connector | 1       | 171-009-203L001 | Norcomp Inc.     | [209FE-ND](http://www.digikey.com/product-detail/en/171-009-203L001/209FE-ND/858108) | [Digi-Key](http://www.digikey.com) |
| Toggle switch On-Off DPST |	1       | M2021SS1W03     | NKK Switches     | [M2021SS1W03-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=M2021SS1W03-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection housing 2-position with locking ramp | 1       | 22-01-3027      | Molex Connector Corporation | [WM2000-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=WM2000-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection housing 3-position with locking ramp | 3       | 22-01-3037      | Molex Connector Corporation | [WM2001-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=WM2001-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection housing 4-position with locking ramp | 1       | 22-01-3047      | Molex Connector Corporation | [WM2002-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=WM2002-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Connection terminal female 22-30 AWG Tin | 15      | 08-50-0114      | Molex Connector Corporation | [WM1114-ND](http://www.digikey.com/product-detail/en/0008500114/WM1114-ND/26475) | [Digi-Key](http://www.digikey.com) |
| 5x5x2 in. Plastic Box with PCB mounting points | 1       | 1598BBK         | Hammond Manufacturing | [HM163-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=HM163-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Power jack connector | 1       | 722A            | Switchcraft, Inc. | [SC1049-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=SC1049-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| AC inlet blade for US | 1       | EMS-US          | CUI, Inc.        |	[T1123-US-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=T1123-US-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| 6 channel 4'' jumper cable | 2       | PRT-10366       | Sparkfun         | [PRT-10366](https://www.sparkfun.com/products/10366) | [Sparkfun](http://www.sparkfun.com) |
| Black 22 AWG 7 stranded hook up wire | 100 ft  | 3051 BK005      | Alpha Wire       | [A2016B-100-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A2016B-100-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Red 22 AWG 7 stranded hook up wire | 100 ft  | 3051 RD005      | Alpha Wire       | [A2016R-100-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A2016R-100-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Orange 22 AWG 7 stranded hook up wire | 100 ft  | 3051 OR005      | Alpha Wire       | [A2016A-100-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A2016A-100-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Yellow 22 AWG 7 stranded hook up wire | 100 ft  | 3051 YL005      | Alpha Wire       | [A2016Y-100-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A2016Y-100-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Purple 22 AWG 7 stranded hook up wire | 100 ft  | 3051 VI005      | Alpha Wire       | [A2016V-100-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A2016V-100-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |
| Blue 22 AWG 7 stranded hook up wire | 100 ft  | 3051 BL005      | Alpha Wire       | [A2016L-100-ND](http://www.digikey.com/scripts/DkSearch/dksus.dll?WT.z_header=search_go&lang=en&keywords=A2016L-100-ND&x=0&y=0&cur=USD) | [Digi-Key](http://www.digikey.com) |

Note: A 100 ft of the hook up wire is not needed, but this is typically the smallest quantity available from suppliers.

### Project Box Hardware ###

| **Description** | **Qty** | **Part Number** | **Manufacturer** | **Order Number** | **Supplier** |
|:----------------|:--------|:----------------|:-----------------|:-----------------|:-------------|
| Screw lock kit for D-sub panel mount | 2       | 20418-0002      | ITT Cannon, LLC  | [1003-1036-ND](http://www.digikey.com/product-detail/en/020418-0002/1003-1036-ND/2403812) | [Digi-Key](http://www.digikey.com) |
| M2x16 machine screw | 4       | 92005A037       | McMaster-Carr    | [92005A037](http://www.mcmaster.com/92005A037) | [McMaster-Carr](http://www.mcmaster.com) |
| M3x10 machine screw | 2       | 92005A120       | McMaster-Carr    | [92005A120](http://www.mcmaster.com/92005A120) | [McMaster-Carr](http://www.mcmaster.com) |
| 4-40 machine screw | 2       | 92949A106       | McMaster-Carr    | [92949A106](http://www.mcmaster.com/92949A106) | [McMaster-Carr](http://www.mcmaster.com) |
| #6 self tapping hex washer head | 4       | 90286A144       | McMaster-Carr    | [90286A144](http://www.mcmaster.com/90286A144) | [McMaster-Carr](http://www.mcmaster.com) |
| M2 nut          | 4       | 90591A111       | McMaster-Carr    | [90591A111](http://www.mcmaster.com/90591A111) | [McMaster-Carr](http://www.mcmaster.com) |
| M2 washer       | 8       | 91166A180       | McMaster-Carr    | [91166A180](http://www.mcmaster.com/91166A180) | [McMaster-Carr](http://www.mcmaster.com) |
| M3 washer       | 2       | 91166A210       | McMaster-Carr    | [91166A210](http://www.mcmaster.com/91166A210) | [McMaster-Carr](http://www.mcmaster.com) |
| 4-40 washer     | 2       | 94744A155       | McMaster-Carr    | [94744A155](http://www.mcmaster.com/94744A155) | [McMaster-Carr](http://www.mcmaster.com) |
| 1/8 in. nylon spacers | 2       | 94639A299       | McMaster-Carr    | [94639A299](http://www.mcmaster.com/94639A299) | [McMaster-Carr](http://www.mcmaster.com) |

## SHT1X Sensor PCB ##

| **Description** | **Qty** | **Part Number** | **Manufacturer** | **Order Number** | **Supplier** |
|:----------------|:--------|:----------------|:-----------------|:-----------------|:-------------|
| 470 Ohm SMD Resistor | 2       | ERJ-12ZYJ471U   | Panasonic - ECG  | [P470WCT-ND](http://www.digikey.com/product-detail/en/ERJ-12ZYJ471U/P470WCT-ND/249703) | [Digi-Key](http://www.digikey.com) |
| 4.7K Ohm SMD Resistor | 2       | ERJ-12ZYJ472U   | Panasonic - ECG  | [P4.7KWCT-ND](http://www.digikey.com/product-search/en?pv7=2&k=P4.7KWCT-ND&mnonly=0&newproducts=0&ColumnSort=0&page=1&quantity=0&ptm=0&fid=0&pageSize=25) | [Digi-Key](http://www.digikey.com) |
| 100nF SMD Capacitor | 1       | GRM155F51C104ZA01D | Murata Electronics | [490-1327-1-ND](http://www.digikey.com/product-detail/en/GRM155F51C104ZA01D/490-1327-1-ND/587931) | [Digi-Key](http://www.digikey.com) |
| Temperature and Relative Humidity Sensor | 1       | SHT15           | Sensirion        | [18M2986](http://www.newark.com/sensirion/sht15/humidity-sensor-8s-4-lcc/dp/18M2986?Ntt=18M2986) | [Newark Electronics](http://www.newark.com/) |
| IC I2C Bus Extender 8-SOIC | 1       | P82B715TD,112   | NXP Semiconductors | [568-3981-5-ND](http://www.digikey.com/product-detail/en/P82B715TD,112/568-3981-5-ND/739477) | [Digi-Key](http://www.digikey.com) |
| 36-position header pins | 1       | 68001-436HLF    | FCI              | [609-2224-ND](http://www.digikey.com/product-search/en?WT.z_header=search_go&lang=en&site=us&keywords=609-2224-ND&x=0&y=0&formaction=on) | [Digi-Key](http://www.digikey.com) |