/*
 * PeteMotorController.h
 *
 *  Created on: 15.11.2016
 *      Author: je
 */

#ifndef PETEMOTORCONTROLLER_H_
#define PETEMOTORCONTROLLER_H_

class Tuple {
public:
	Tuple(double l, double r) : l(l), r(r) {}
	double l;
	double r;
};

class PeteMotorController {
public:
	enum Mode {POWER, SPEEDS};
	virtual Tuple getVelocities() = 0;
	virtual Tuple getCommands() = 0;
	virtual Mode getMode() { return POWER; } ;
	virtual void update() = 0;
	virtual ~PeteMotorController() { }
};

#endif /* PETEMOTORCONTROLLER_H_ */
