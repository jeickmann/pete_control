/*
 * PetePS3Controller.cpp
 *
 *  Created on: 15.11.2016
 *      Author: je
 */

#include "PetePS3Controller.h"
#include "Wire.h"

void PetePS3Controller::readPS3() {
	uint8_t *ps3Ptr = (uint8_t *)&ps3;    // Create pointer to ps3 struct

	unsigned char data_values_rcvd=0;     // keep track of how many characters received
	Wire.beginTransmission(I2C_ADDRESS);  // transmit to device
	Wire.write(0);                        // Start receiving data from register 0
	Wire.endTransmission();               // end transmission
	// To retrieve all data we need 35 bytes, but restriction in Arduino means
	// we can only get 32 bytes at one go, so we split it into 2 reads

	Wire.requestFrom(I2C_ADDRESS, 28);    // request 28 bytes from PS3
	data_values_rcvd=0;
	while(Wire.available())
	{
	*ps3Ptr++ = Wire.read();            // receive a byte and increment pointer address
	data_values_rcvd++;
	}
	Wire.beginTransmission(I2C_ADDRESS);  // transmit to device
	Wire.write(28);                       // Start receiving data from register 28
	Wire.endTransmission();               // end transmission
	Wire.requestFrom(I2C_ADDRESS, PS3_DATA_SIZE-28);    // request outstanding bytes from PS3
	while(Wire.available())
	{
	*ps3Ptr++ = Wire.read();            // receive a byte and increment pointer address
	data_values_rcvd++;
	}
}

PetePS3Controller::PetePS3Controller() {
	Wire.begin();
}

void PetePS3Controller::update() {
	readPS3();
	commands = Tuple(ps3.joy_left_y, ps3.joy_right_y);
}
