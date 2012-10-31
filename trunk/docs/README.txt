******************************************************
* NRL-SHT1x Temperature and Relative Humidity Sensor *
******************************************************

Created by: Christopher R. Field <christopher.field@nrl.navy.mil>

The NRL T-RH Sensor Hub code base is designed to read the temperature and relative
humidity from up to three Sensirion SHT15 sensors. The Arduino Uno and
relative microcontroller from Atmel (Atmega368P) are used to communicate with three
sensors and a computer. The box containing the microcontroller, power
supply, LCD, and connectors to the three sensors is the hub and is the
master in the I2C-bus protocol. The three sensors are the slaves. Bus
extenders are used to allow communication with the three sensors at
cable lengths greater than 10 cm to approximately 1000 meters.

= Installation =

== Arduino IDE ==

Download and install the Arduino Integrated Development Environment (IDE) version 1.0.1 or 
newer prior to proceeding with the installation. Once the IDE is installed, follow the
directions from the IDE and the Arduino website (http://www.arduino.cc) for installing
the Uno drivers and connecting an Arduino Uno to a computer for uploading code.

Once the IDE and drivers are installed and an Arduino Uno is connected to a computer via
the USB port, copy the SHT1x library to the library folder of the Arduino
IDE. The library folder is typically located at C:\path\to\IDE\libraries for the
Windows operating system. In other words, the libraries folder is located in the same
folder as the arduino.exe file. Restart the IDE. The library should now be present in the 
list of libraries in the IDE. If not, review the steps available with the IDE for 
installing and using user-created libraries.

Select the communications (COM) port the Arduino Uno is connected to within the IDE. Make
sure all jumpers and shields have been removed from the circuits and the Uno prior to 
uploading. Uploading code to the Uno is a delicate process and extra circuits and 
electrical connections make disrupt the upload process. Open the NRL-SHT1x.ino file within
the IDE and upload the code to the microcontroller. For additional details on uploading
code, see the IDE documentation or the Arduino website (http://www.arduino.cc).

Once the code has been successfully uploaded to the controller, the chip can be mounted
into the 28-pin DIP socket on the printed circuit board in the box.

= Communication =

A MAX233 chip is used to convert TTL level signals to RS-232 levels for serial communication
with a computer. Communication is established with 19200 baud rate, 8 data bits, 1 stop bit,
no parity, and no hardware flow control. The commands are listed below:
 
TC1?    Gets the temperature in C from Sensor 1
TC2?    Gets the temperature in C from Sensor 2
TC3?    Gets the temperature in C from Sensor 3
TF1?	Gets the temperature in F from Sensor 1
TF2?	Gets the temperature in F from Sensor 2
TF3?	Gets the temperature in F from Sensor 3
RH1?    Gets the relative humidity in % from Sensor 1
RH2?    Gets the relative humidity in % from Sensor 2
RH3?    Gets the relative humidity in % from Sensor 3

The sensor hub will return "ERROR 01" if the command is not recognized and "ERROR 02" if the
sensor number is not between 1 and 3.

= Versions =

Version 1.0.0 is the base implementation of the software that includes communication with all
three sensors and a computer. This version is designed to work with a printed circuit board
(PCB) that acts as a shield for a Arduino Uno.
 
Version 2.0.0 is designed to work with a 4-layer printed circuit board (PCB) with the inner
layers being 5V (VCC) and Ground (GND), repsectively. The top and bottom layers are for
signals. The PCB is slightly different from v1.0.0 in that it is designed to fit into a
different box and uses a slightly modified circuit to communicate with remote SHT1x 
temperature and relative humidity sensors. The modified circuit does not effect the
operation or execution of the code.

Version 2.1.0 uses integer arrays instead of float arrays for storing the most recent temperatures
and relative humidities. It also detects if sensors are connected to any of the ports and disables
reading of the sensor if not connected. It will only scroll the temperature and relative humidity
for the sensors connected on the LCD screen. This is done because there is apparently a problem
with reading the temperature and relative humidities of sensors across the RS-232 protocol to a
computer where it can take up to 2 seconds for the values to be read. This is a problem and should
happen a lot faster. The baud rate has been increased to 19200. This version also adds the following
commands:
 
C1?    Gets connectivity of Sensor 1, will return 0 if not connected and 1 if connected
C2?    Gets connectivity of Sensor 1, will return 0 if not connected and 1 if connected
C3?    Gets connectivity of Sensor 1, will return 0 if not connected and 1 if connected
 
Version 2.1.1 fixes an issue with timing that would cause delays in sending data to a computer over
the RS-232 protocol because the microcontroller was waiting on the sensor to send data back. The
SHT1x library will have to be re-written to avoid this locking issue in the future and provide
a more elegant fix, but this version is a quick fix. Each read command requires a maximum of
320 ms. If all three sensors are reading both measurements, then the total time is 1920 ms. The
fastest the data can be updated with this version is 2000 ms, or 2 secs. Thus, the computer should
only pull for readings via the serial port every two seconds.
 
Version 3.0.0 restructures the source code to use the Eclipse IDE with the AVR plugin instead
of the Arduino IDE. The Eclipse IDE is more feature-rich and flexible. Additionally, the code
has been updated to use the printed circuit board v2.2 with the MAX232 chip instead of the
MAX233, which was causing communication problems. The communication protocol between
the sensor hub and the sensors has also been changed so waiting for the sensor to response
does not lock the microcontroller. The sensor hub now actively checks connectivity, not just
at startup. The LCD will display "NC" if the sensor is not connected and "NaN" for "Not a
Number" if the readings from a sensor are meaningless or out of range for the sensor. The LCD
has been updated to display the temperature (in Celcius) and relative humidtiy for all three
sensors simultaneously.

The serial commands have also been updated for v3.0.0 to the following:

TC1?		Gets the temperature from Sensor 1 in Celcius
TC2?		Gets the temperature from Sensor 2 in Celcius
TC3?		Gets the temperature from Sensor 3 in Celcius
TF1?		Gets the temperature from Sensor 1 in Fahrenheit
TF2?		Gets the temperature from Sensor 2 in Fahrenheit
TF3?		Gets the temperature from Sensor 3 in Fahrenheit
RH1?		Gets the relative humidity from Sensor 1 in percent
RH2?		Gets the relative humidity from Sensor 2 in percent
RH3?		Gets the relative humidity from Sensor 3 in percent

The connectivity commands from Version 2.1.0 have been removed since the hub now actively checks
for connectivity all the time. If a command is not recognized, the hub will return "ERROR 01".
If the sensor number (1-3) is out of bounds, it will return "ERROR 02". 