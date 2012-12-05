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
three sensors and a computer.
 
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

Version 1.0.1 fixes a bug with displaying relative humidity less than 10%. The decimal place
would not align properly and the "N" would not clear if the relative humidity was less than
10%. 