/*
 * PeteSerialCom.h
 *
 *  Created on: 09.11.2016
 *      Author: je
 */

#ifndef PETESERIALCOM_H_
#define PETESERIALCOM_H_

#include "PeteMotor.h"
#include "SoftwareSerial.h"

class PeteSerialCom {
public:
	PeteSerialCom(PeteMotor * left, PeteMotor * right, int rx, int tx);
	virtual ~PeteSerialCom();
	void update();
private:
	void sendVelocities();
	PeteMotor * left;
	PeteMotor * right;
	SoftwareSerial btSerial;
};

#endif /* PETESERIALCOM_H_ */
