/*
 * PetePS3Controller.h
 *
 *  Created on: 15.11.2016
 *      Author: je
 */

#ifndef PETEPS3CONTROLLER_H_
#define PETEPS3CONTROLLER_H_

#include "PeteMotorController.h"

class PetePS3Controller: public PeteMotorController {
private:
	Tuple velocities;
	Tuple commands;
	const static int I2C_ADDRESS = 41;
	const static int PS3_DATA_SIZE = 35;

	struct ps3_data {
	  unsigned char joy_left_x;
	  unsigned char joy_left_y;
	  unsigned char joy_right_x;
	  unsigned char joy_right_y;
	  unsigned char accel_x;
	  unsigned char accel_y;
	  unsigned char press_up;
	  unsigned char press_right;
	  unsigned char press_down;
	  unsigned char press_left;
	  unsigned char press_lb;
	  unsigned char press_rb;
	  unsigned char press_lt;
	  unsigned char press_rt;
	  unsigned char press_triangle;
	  unsigned char press_circle;
	  unsigned char press_x;
	  unsigned char press_square;
	  unsigned char btn_left;
	  unsigned char btn_down;
	  unsigned char btn_right;
	  unsigned char btn_up;
	  unsigned char btn_start;
	  unsigned char btn_joy_right;
	  unsigned char btn_joy_left;
	  unsigned char btn_select;
	  unsigned char btn_square;
	  unsigned char btn_x;
	  unsigned char btn_circle;
	  unsigned char btn_triangle;
	  unsigned char btn_rt;
	  unsigned char btn_lt;
	  unsigned char btn_rb;
	  unsigned char btn_lb;
	  unsigned char btn_ps3;
	} ;

	ps3_data ps3;
	void readPS3();

public:
	virtual PetePS3Controller();
	virtual Tuple getVelocities() { return velocities; };
	virtual Tuple getCommands() { return commands; };
	virtual void update();
};

#endif /* PETEPS3CONTROLLER_H_ */
