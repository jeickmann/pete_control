/*
 * PeteMotor.cpp
 *
 *  Created on: 07.11.2016
 *      Author: je
 */

#include "Arduino.h"
#include "PeteMotor.h"

#define Kp 0.05
#define Ki 0.2
#define Kd 0.0

PeteMotor * PeteMotor::count1Ptr = 0;
PeteMotor * PeteMotor::count2Ptr = 0;

void PeteMotor::int1Count() {
	count1Ptr->count();
}

void PeteMotor::int2Count() {
	count2Ptr->count();
}

PeteMotor::PeteMotor(int dirPin, int pwmPin, int counterPin, int counterNum)
	: dirPin(dirPin), pwmPin(pwmPin), counterPin(counterPin),
	  power(0.0f), distance(0), lastTick(0), velocity(0),
	  //pid(&velocity, &power, &speed,Kp,Ki,Kd, DIRECT)
	  pid(&input, &output, &setpoint,Kp,Ki,Kd, DIRECT)
	{
	pid.SetOutputLimits(0, 1);
	if(counterNum == 0) {
		count1Ptr = this;
	} else {
		count2Ptr = this;
	}

	pinMode(dirPin, OUTPUT);
	pinMode(pwmPin, OUTPUT);

	digitalWrite(dirPin, LOW);
	digitalWrite(pwmPin, LOW);

	if(counterNum == 0) {
		attachInterrupt(digitalPinToInterrupt(counterPin), PeteMotor::int1Count, RISING);
	} else {
		attachInterrupt(digitalPinToInterrupt(counterPin), PeteMotor::int2Count, RISING);
	}
}

PeteMotor::~PeteMotor() {

}

void PeteMotor::setPower(double power) {
	this->power = power;

	digitalWrite(dirPin, power>0?LOW:HIGH);
	int pwmValue = abs(power) * 255;
	analogWrite(pwmPin, pwmValue);
}

int PeteMotor::getDistance() {
	return distance;
}

void PeteMotor::count() {
	distance += power>0?1:-1;
	velocity = 1000.0f / (millis() - lastTick) / TICKS_PER_METER;
	if(power < 0) {
		velocity *= -1;
	}
	lastTick = millis();
}

double PeteMotor::getPower() {
	return power;
}

double PeteMotor::getVelocity() {
	return velocity;
}

double PeteMotor::getSpeed() const {
	return speed;
}

void PeteMotor::setSpeed(double speed) {
	this->speed = speed;
	pid.SetMode(AUTOMATIC);
}

void PeteMotor::autoPower() {
	if(millis() - lastTick > 1000) {
		velocity = 0;
		lastTick = millis();
	}
	input = abs(velocity);
	if(velocity * speed < 0) {
		input = 0;
	}
	setpoint = abs(speed);
	pid.Compute();
	setPower(output * ((speed>=0)?1:-1));
}
