/*
 * PeteMotor.h
 *
 *  Created on: 07.11.2016
 *      Author: je
 */

#ifndef PETEMOTOR_H_
#define PETEMOTOR_H_

#include "PID_v1.h"

#define PETE_SPEED_SAMPLING_HZ 10
#define TICKS_PER_METER 1

class PeteMotor {
private:
	int dirPin;
	int pwmPin;
	int counterPin;
	double power;
	int distance;
	double speed;

	double input;
	double output;
	double setpoint;

	static PeteMotor * count1Ptr;
	static PeteMotor * count2Ptr;
	unsigned long int lastTick;
	double velocity;
	PID pid;

	static void int1Count();
	static void int2Count();

public:
	PeteMotor(int dirPin, int pwmPin, int counterPin, int counterNum);
	virtual ~PeteMotor();

	void count();
	void setPower(double power);
	double getPower();
	int getDistance();

	double getVelocity();
	double getSpeed() const;
	void setSpeed(double speed);
	void autoPower();
};

#endif /* PETEMOTOR_H_ */
