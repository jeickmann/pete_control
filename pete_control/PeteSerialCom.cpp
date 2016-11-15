/*
 * PeteSerialCom.cpp
 *
 *  Created on: 09.11.2016
 *      Author: je
 */

#include "PeteSerialCom.h"
#include "Arduino.h"
PeteSerialCom::PeteSerialCom(PeteMotor * left, PeteMotor * right, int rx, int tx)
	: left(left), right(right), btSerial(rx, tx) {
	btSerial.begin(38400);

}

PeteSerialCom::~PeteSerialCom() {

}

void PeteSerialCom::update() {
	if (btSerial.available()) {
		Serial.println("Reading");
		char c = btSerial.read();
		if (c == '?') {
			sendVelocities();
		} else if (c == '#') {
			double cmds[2];
			btSerial.readBytes((char*)cmds, 2*sizeof(double));
			left->setPower(cmds[0]);
			right->setPower(cmds[1]);
		}
	}
}

void PeteSerialCom::sendVelocities() {
	double speeds[2] = {left->getVelocity(), right->getVelocity() };
	btSerial.write((char*) speeds, sizeof(double) * 2);
}
