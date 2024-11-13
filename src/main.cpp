/**
 * \file main.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "main.h"

nova::Drive drive = nova::Drive();

//std::string autonSelection;

void initialize() {
    drive.initialize();
    
    drive.resetMotorEncoders();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	while (1) {
		drive.run();

		pros::delay(10);
	}
}