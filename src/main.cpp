/**
 * \file main.cpp
 *
 * \brief Main file
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#include "main.h"

Nova::Brain brain = Nova::Brain();
Nova::Drive drive = Nova::Drive();
Nova::Intake intake = Nova::Intake();
Nova::Clamp clamp = Nova::Clamp();

void initialize() {
    pros::lcd::initialize();

    drive.initialize();
}

void disabled() {}

void competition_initialize() {
    brain.initialize();

    drive.initialize();

    autonomous();
}

void autonomous() {
    // Nova::moveToPos(10.0, 10.0, M_PI / 2.0); // 10 cm, 10 cm, 90 degrees
}

void opcontrol() {
    while (true) {
        Nova::update(); // tracking algorithm loop

        drive.run();

        pros::delay(10);
    }
}
