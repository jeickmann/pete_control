#include "Arduino.h"
#include "PeteMotor.h"
#include "PeteSerialCom.h"
#include "PetePS3Controller.h"

int dirPin[2] = {9,12};
int pwmPin[2] = {11,6};

PeteMotor * right;
PeteMotor * left;
PeteSerialCom * com;
PeteMotorController * controller;

unsigned long nextSpeedChange;
//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(38400);
	right = new PeteMotor(9, 11, 3, 0);
	left = new PeteMotor(12, 6, 2, 1);
	com = new PeteSerialCom(left, right, 4, 7);
	controller = new PetePS3Controller();
	//left->setPower(-0.5);
	//left->setSpeed(-15);
	nextSpeedChange = millis() + 5000;
}

unsigned long int nextTick = 0;
unsigned long int interval = 1000;

// The loop function is called in an endless loop
void loop()
{
	//com->update();
	controller->update();
	Tuple cmds = controller->getCommands();
	left->setPower(cmds.l);
	right->setPower(cmds.r);
	/*
	left->autoPower();
	if(millis() > nextTick) {
		Serial.print(left->getPower());
		Serial.print(" -> ");
		Serial.print(left->getVelocity());
		Serial.print(" (");
		Serial.print(left->getSpeed());
		Serial.println(")");
		nextTick = millis() + interval;
		//left->setSpeed(left->getSpeed() * -1);
	}

	if(millis() > nextSpeedChange) {
		nextSpeedChange = millis() + 3000;
		//left->setSpeed(left->getSpeed()==15?8:15);
	}
	*/
}
