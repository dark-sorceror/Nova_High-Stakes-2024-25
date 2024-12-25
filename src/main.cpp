/**
 * \file main.cpp
 *
 * \brief Main file
 * 
 * \date Updated - 12/25/2024
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
    intake.initialize();

    autonomous();
}

/**
 * @brief Autonomous
 * 
 */
void autonomous() {
    if (!Nova::imu1.is_calibrating() && !Nova::imu2.is_calibrating()) {
        auton.test();
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