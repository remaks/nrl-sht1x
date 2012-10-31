/*
 * main.cpp
 *
 * Created by: Christopher R. Field <christopher.field@nrl.navy.mil, cfield2@gmail.com>
 * Version: 1.0.0
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * A control box for reading the temperature and relative humidity from three SHT15 sensors from
 * Sensirion. The SHT15 sensor uses a psuedo-I2C communication protocol, which is typically
 * limited to a distance of 10 cm. The I2C distance is extended for each sensor connection to
 * 100 cm using a pair of I2C-extenders from NXP Semiconductor. The I2C extenders must be used
 * as a pair, one at the sensor hub and the other at the SHT15 sensor. The extenders are
 * invisible to the software and the communications are conducted similar to the I2C protocol.
 * A liquid crystal display (LCD) is used to report the temperature and relative humidity for
 * all three sensors in addition to the serial computer communication.
 *
 * Each sensor requires 2 digital lines (DATA and SCK), VCC (5V), and GND. The liquid crystal
 * display (LCD) requires 6 pins to operate.
 *
 * A MAX233 chip is used to convert TTL level signals to RS-232 levels for serial communication
 * with a computer. Communication is established with 19200 baud rate, 8 data bits, 1 stop bit,
 * no parity, and no hardware flow control. The commands are listed below:
 *
 * TC1?		Gets the temperature from Sensor 1 in Celcius
 * TC2?		Gets the temperature from Sensor 2 in Celcius
 * TC3?		Gets the temperature from Sensor 3 in Celcius
 * TF1?		Gets the temperature from Sensor 1 in Fahrenheit
 * TF2?		Gets the temperature from Sensor 2 in Fahrenheit
 * TF3?		Gets the temperature from Sensor 3 in Fahrenheit
 * RH1?		Gets the relative humidity from Sensor 1 in percent
 * RH2?		Gets the relative humidity from Sensor 2 in percent
 * RH3?		Gets the relative humidity from Sensor 3 in percent
 *
 * If a command is not recognized, the hub will return "ERROR 01". If the sensor number (1-3) is
 * out of bounds, it will return "ERROR 02".
 */
#include <Arduino.h>
#include <LiquidCrystal.h>

/*
 * LCD constants.
 */
const int LCD_RS = 8;
const int LCD_ENABLE = 9;
const int LCD_D4 = 10;
const int LCD_D5 = 11;
const int LCD_D6 = 12;
const int LCD_D7 = 13;
const int LCD_NUM_COLS = 16;
const int LCD_NUM_ROWS = 2;
const int LCD_PRECISION = 1; // Number of decimal places
const int CURSOR_OFFSET = 5; // The spacing between sensor readings on the LCD
const unsigned long LCD_DELAY = 2000; // milliseconds

/*
 * Sensor communications.
 */
const int SENSOR_1_SDA = 2;
const int SENSOR_1_SCL = 3;
const int SENSOR_2_SDA = 4;
const int SENSOR_2_SCL = 5;
const int SENSOR_3_SDA = 6;
const int SENSOR_3_SCL = 7;
const int T_COMMAND = 0b00000011; // see SHT15 datasheet
const int RH_COMMAND = 0b00000101; // see SHT15 datasheet
const int T_PRECISION = 1; // Number of decimal places
const int RH_PRECISION = 1; // Number of decimal places
const unsigned long READ_DELAY = 1000;

/*
 * Sensor constants.
 */
const int NUM_SENSORS = 3;
const int SENSOR_1 = 0;
const int SENSOR_2 = 1;
const int SENSOR_3 = 2;
const unsigned long SENSOR_TIMEOUT = 2500; // milliseconds
const float DC1 = -40.0; // Temperature in C constant, see SHT15 datasheet
const float DC2 = 0.01; // Temperature in C constant, see SHT15 datasheet
const float DF1 = -40.0; // Temperature in F constant, see SHT15 datasheet
const float DF2 = 0.018; // Temperature in F constant, see SHT15 datasheet
const float C1 = -2.0468; // Humidity constant, see SHT15 datasheet
const float C2 = 0.0367; // Humidity constant, see SHT15 datasheet
const float C3 = -1.5955E-6; // Humidity constant, see SHT15 datasheet
const float T1 = 0.01; // Humidity constant, see SHT15 datasheet
const float T2 = 0.00008; // Humidity constant, see SHT15 datasheet
const float MAX_TEMPERATURE = 123.8; // C
const float MIN_TEMPERATURE = -40.0; // C
const float MAX_HUMIDITY = 100.0; // %
const float MIN_HUMIDITY = 0.0; // %

/*
 * Serial communications.
 */
const int BAUD_RATE = 19200;
const char TERMINATION_CHAR = '\n';
const int ASCII_ZERO = 48;
const unsigned long SERIAL_TIMEOUT = 1000; // milliseconds
const char C_UNIT = 'C';
const char F_UNIT = 'F';
const char H_UNIT = '%';

/*
 * Variables
 */
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

unsigned long currentTime = 0; // milliseconds
unsigned long lastUpdate = 0; // milliseconds

int command[NUM_SENSORS]; // Either T_COMMAND or RH_COMMAND;
int started[NUM_SENSORS]; // 0 = false, 1 = true
int acknowledged[NUM_SENSORS]; // 0 = false, 1 = true
int connected[NUM_SENSORS]; // 0 = false, 1 = true
int released[NUM_SENSORS]; // 0 = false, 1 = true
int measured[NUM_SENSORS]; // 0 = false, 1 = true
int dataPins[NUM_SENSORS];
int clockPins[NUM_SENSORS];
int temperatures[NUM_SENSORS];
int humidities[NUM_SENSORS];
unsigned long lastRead[NUM_SENSORS]; // milliseconds
unsigned long waitTimes[NUM_SENSORS]; // milliseconds

/*
 * Gets the temperature in Celsius.
 *
 * @param _temperature The raw temperature from a sensor.
 * @return The temperature in C.
 */
float getTC(int _temperature) {
	return (_temperature * DC2) + DC1;
}

/*
 * Gets the temperature in Fahrenheit.
 *
 * @param _temperature The raw temperature from a sensor.
 * @return The temperature in F.
 */
float getTF(int _temperature) {
	return (_temperature * DF2) + DF1;
}

/*
 * Gets the temperature compensated relative humidity.
 *
 * @param _humidity The raw humidity from a sensor.
 * @param _temperature The raw temperature from a sensor.
 * @return The relative humidity.
 */
float getRH(int _humidity, int _temperature) {
	float linearHumidity;
	float correctedHumidity;

	linearHumidity = C1 + C2 * _humidity + C3 * _humidity * _humidity;
	correctedHumidity = (getTC(_temperature) - 25.0) * (T1 + T2 * _humidity) + linearHumidity;

	return correctedHumidity;
}

/*
 * Reads the measured value from a sensor.
 *
 * @param _dataPin The data pin
 * @param _clockPin The clock pin
 * @return The integer value of the measurement that must be converted.
 */
int readMeasurement(int _dataPin, int _clockPin) {

	// Get the first 8 bits.
	int measurement = shiftIn(_dataPin, _clockPin, MSBFIRST);
	measurement *= 256;

	// Send acknowledgment of the first 8 bits.
	pinMode(_dataPin, OUTPUT);
	digitalWrite(_dataPin, LOW);
	digitalWrite(_clockPin, HIGH);
	digitalWrite(_clockPin, LOW);

	// Get the last 8 bits.
	pinMode(_dataPin, INPUT);
	measurement |= shiftIn(_dataPin, _clockPin, MSBFIRST);

	// Skip the CRC.
	pinMode(_dataPin, OUTPUT);
	digitalWrite(_dataPin, HIGH);
	digitalWrite(_clockPin, HIGH);
	digitalWrite(_clockPin, LOW);

	return measurement;
}

/*
 * Reads the serial buffer until the TERMINATION_CHAR is reached or timeout.
 * Will return "ERROR 01" as the command if the timeout was reached before
 * the termination character was read.
 *
 * @return The command from the serial buffer.
 */
String readSerialCommand() {
	String command = "";
	char readChar = 0x00;

	unsigned long timeout = millis() + SERIAL_TIMEOUT; // milliseconds

	while (readChar != TERMINATION_CHAR && millis() < timeout) {
		delay(10);
		readChar = Serial.read();
		command = command + readChar;
	}

	if ( readChar == TERMINATION_CHAR ) {
		command.trim();
	} else {
		command = "ERROR 01";
	}

	return command;
}

/*
 * Prints the temperature of a sensor to the LCD.
 *
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * | T | T | . | T |   | T | T | . | T |   | T | T | . | T |   | C | = Row 1
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |   | H | H | H |   |   | H | H | H |   |   | H | H | H |   | % | = Row 2
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| = Col
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *
 * @param _sensor The sensor index.
 */
void lcdPrintTemperature(int _sensor) {

	int cursorPosition = _sensor * CURSOR_OFFSET;
	lcd.setCursor(cursorPosition, 0);

	if ( connected[_sensor] ) {
		// TODO: Add unit change option.
		float displayTemperature = getTC(temperatures[_sensor]);
		int lcdPrecision = LCD_PRECISION;

		if ( displayTemperature > MAX_TEMPERATURE ) {
			lcd.print(" MAX");
		} else if ( displayTemperature < MIN_TEMPERATURE ) {
			lcd.print(" MIN");
		} else {

			// Provide extra space and decrease in precision if the temperature is greater than 100C
			// or negative.
			if ( displayTemperature >= 100.0 || displayTemperature < 0.0 ) {
				lcd.print(" ");
				lcdPrecision = 0;
			}

			lcd.print(displayTemperature, lcdPrecision);
		}

	} else {
		lcd.print(" NC ");
	}
}

/*
 * Prints the relative humidity of a sensor to the LCD.
 *
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * | T | T | . | T |   | T | T | . | T |   | T | T | . | T |   | C | = Row 1
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |   | H | H | H |   |   | H | H | H |   |   | H | H | H |   | % | = Row 2
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14| 15| = Col
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 *
 * @param _sensor The sensor index.
 */
void lcdPrintHumidity(int _sensor) {
	int cursorPosition = _sensor * CURSOR_OFFSET;
	lcd.setCursor(cursorPosition, 1);

	if ( connected[_sensor] ) {
		float displayHumidity = getRH(humidities[_sensor], temperatures[_sensor]);
		int lcdPrecision = LCD_PRECISION;

		if ( displayHumidity > MAX_HUMIDITY ) {
			lcd.print(" MAX");
		} else if ( displayHumidity < MIN_HUMIDITY ) {
			lcd.print(" MIN");
		} else {
			lcd.print(displayHumidity, lcdPrecision);
		}

	} else {
		lcd.print(" NC ");
	}
}

/*
 * Resets sensor communication.
 *
 * @param _sensor The sensor index.
 */
void reset(int _sensor) {
	// Reset the communication sequence for the sensor.
	started[_sensor] = false;
	acknowledged[_sensor] = false;
	released[_sensor] = false;
	measured[_sensor] = false;
}

/*
 * Sets up the microcontroller. This method is only called once on power up.
 */
void setup() {
	Serial.begin(BAUD_RATE);
	lcd.begin(LCD_NUM_COLS, LCD_NUM_ROWS);

	// Initialize the communication arrays for all the sensors.
	for (int sensor = 0; sensor < NUM_SENSORS; sensor++) {
		command[sensor] = T_COMMAND;
		connected[sensor] = false;

		reset(sensor);

		if ( sensor == SENSOR_1 ) {
			dataPins[sensor] = SENSOR_1_SDA;
			clockPins[sensor] = SENSOR_1_SCL;
		} else if ( sensor == SENSOR_2 ) {
			dataPins[sensor] = SENSOR_2_SDA;
			clockPins[sensor] = SENSOR_2_SCL;
		} else if ( sensor == SENSOR_3 ) {
			dataPins[sensor] = SENSOR_3_SDA;
			clockPins[sensor] = SENSOR_3_SCL;
		}

		temperatures[sensor] = MIN_TEMPERATURE;
		humidities[sensor] = MIN_HUMIDITY;

		lastRead[sensor] = millis();
		waitTimes[sensor] = millis();
	}

	// Print some startup information to the user.
	// NRL = Naval Research Laboratory.
	lcd.print("T-RH Sensor Hub");
	lcd.setCursor(0, 1);
	lcd.print("NRL v1.0.0");

	// Allow time for the user to read the LCD information. This
	// also allows the sensors to end sleep mode after power up,
	// which is necessary for communication.
	delay(3000);

	// Display the main screen.
	lcd.clear();
	lcd.setCursor(15, 0);
	lcd.print(C_UNIT);
	lcd.setCursor(15, 1);
	lcd.print(H_UNIT);
}

/*
 * Continuously runs while the microcontroller is on after set up.
 */
void loop() {

	currentTime = millis();

	for (int sensor = 0; sensor < NUM_SENSORS; sensor++) {
		if ( !started[sensor] && ((currentTime - lastRead[sensor]) > READ_DELAY) ) {
			started[sensor] = true;
			waitTimes[sensor] = millis();

			// Start the transmission.
			pinMode(dataPins[sensor], OUTPUT);
			pinMode(clockPins[sensor], OUTPUT);

			digitalWrite(dataPins[sensor], HIGH);
			digitalWrite(clockPins[sensor], HIGH);
			digitalWrite(dataPins[sensor], LOW);
			digitalWrite(clockPins[sensor], LOW);
			digitalWrite(clockPins[sensor], HIGH);
			digitalWrite(dataPins[sensor], HIGH);
			digitalWrite(clockPins[sensor], LOW);

			// Send the command.
			shiftOut(dataPins[sensor], clockPins[sensor], MSBFIRST, command[sensor]);
			pinMode(dataPins[sensor], INPUT);
		}

		// Wait for acknowledgment of the command.
		if ( !acknowledged[sensor] && started[sensor] ) {
			int acknowledgeBit = digitalRead(dataPins[sensor]);

			if ( acknowledgeBit == LOW ) {
				connected[sensor] = true;
				acknowledged[sensor] = true;
				waitTimes[sensor] = millis();

				digitalWrite(clockPins[sensor], HIGH);
				digitalWrite(clockPins[sensor], LOW);
			} else {
				if ( (currentTime - waitTimes[sensor]) > SENSOR_TIMEOUT ) {

					// Sensor communication has timed out, most likely because
					// the sensor is not connected.
					reset(sensor);
					connected[sensor] = false;
					waitTimes[sensor] = 0;
				}
			}
		}

		// Wait for release of DATA line.
		if ( !released[sensor] && acknowledged[sensor] ) {
			int releaseBit = digitalRead(dataPins[sensor]);

			if ( releaseBit == HIGH ) {
				released[sensor] = true;
				waitTimes[sensor] = millis();
			} else {
				if ( (currentTime - waitTimes[sensor]) > SENSOR_TIMEOUT ) {

					// Sensor communication has timed out, most likely because
					// the sensor is not connected.
					reset(sensor);
					connected[sensor] = false;
					waitTimes[sensor] = 0;
				}
			}
		}

		// Wait for sensor to complete measurement.
		if ( !measured[sensor] && released[sensor] ) {
			int measurementBit = digitalRead(dataPins[sensor]);

			if ( measurementBit == LOW ) {
				measured[sensor] = true;
				waitTimes[sensor] = millis();
			} else {
				if ( (currentTime - waitTimes[sensor]) > SENSOR_TIMEOUT ) {

					// Sensor communication has timed out, most likely because
					// the sensor is not connected.
					reset(sensor);
					connected[sensor] = false;
					waitTimes[sensor] = 0;
				}
			}
		}

		// Obtain the measurement.
		if ( measured[sensor] ) {
			if ( command[sensor] == T_COMMAND ) {
				temperatures[sensor] = readMeasurement(dataPins[sensor],
						clockPins[sensor]);

				// Run the humidity command next.
				command[sensor] = RH_COMMAND;
			} else if ( command[sensor] == RH_COMMAND ) {
				humidities[sensor] = readMeasurement(dataPins[sensor],
						clockPins[sensor]);

				// Run the temperature command next.
				command[sensor] = T_COMMAND;
			} else {
				// Error
			}

			// Reset the communication sequence for the sensor.
			reset(sensor);
			lastRead[sensor] = currentTime;
			waitTimes[sensor] = 0;
		}
	}

	// Update the LCD.
	if ( (currentTime - lastUpdate) > LCD_DELAY ) {
		for (int sensor = 0; sensor < NUM_SENSORS; sensor++) {
			lcdPrintTemperature(sensor);
			lcdPrintHumidity(sensor);
		}

		lastUpdate = millis();
	}

	// Serial communication.
	if ( Serial.available() ) {
		String command = readSerialCommand();

		if ( command.endsWith("?") ) {

			// Convert to an integer by subtracting ASCII zero (48) from the ASCII character
			// value, then decrement by one to convert to array index from sensor number.
			int sensor = (command.charAt(2) - ASCII_ZERO) - 1;

			// Check if sensor index is in bounds.
			if ( sensor < NUM_SENSORS && sensor >= 0 ) {
				if ( connected[sensor] ) {
					if ( command.startsWith("T") ) {
						if ( command.charAt(1) == C_UNIT ) {
							float serialTC = getTC(temperatures[sensor]);

							Serial.print(serialTC, T_PRECISION);
							Serial.println();
						} else if ( command.charAt(1) == F_UNIT ) {
							float serialTF = getTF(temperatures[sensor]);

							Serial.print(serialTF, T_PRECISION);
							Serial.println();
						}
					} else if ( command.startsWith("R") ) {

						float serialRH = getRH(humidities[sensor],
								temperatures[sensor]);

						Serial.print(serialRH, RH_PRECISION);
						Serial.println();
					}
					else {
						Serial.print("ERROR 01"); // command not recognized
						Serial.println();
					}
				}
				else {
					Serial.print("NC"); // Not Connected
					Serial.println();
				}
			}
			else {
				Serial.print("ERROR 02"); // Out of range
				Serial.println();
			}
		}
	}
}
