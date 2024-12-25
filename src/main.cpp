/**
 * \file main.cpp
 *
 * \brief Main file
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include "main.h"

Nova::Brain brain = Nova::Brain();

Nova::Chassis chassis = Nova::Chassis();

Nova::Intake intake = Nova::Intake();

Nova::Clamp clamp = Nova::Clamp();
Nova::Auton auton = Nova::Auton(chassis, intake, clamp);

/**
 * @brief Initialize
 * 
 */
void initialize() {
    //pros::lcd::initialize();
    brain.initialize();

    chassis.initialize();
    Nova::imu1.reset();
    Nova::imu2.reset();

    intake.initialize();
}

void disabled() {}

/**
 * @brief Competition Initialize
 * 
 */
void competition_initialize() {
    brain.initialize();

    chassis.initialize();
    Nova::imu1.reset();
    Nova::imu2.reset();

    intake.initialize();

    autonomous();
}

/**
 * @brief Autonomous
 * 
 */
void autonomous() {
    if (!Nova::imu1.is_calibrating() && !Nova::imu2.is_calibrating()) {
        auton.blue1Elims();
    }
}

/**
 * @brief User Control
 * 
 */
void opcontrol() {
    while (true) {
        //Nova::update(); // tracking algorithm loop

        chassis.run();

        intake.run();
        clamp.run();

        //Nova::ctr.print(0, 0, "%0.2f", chassis.getIMURotation());

        pros::delay(10);
    }
}