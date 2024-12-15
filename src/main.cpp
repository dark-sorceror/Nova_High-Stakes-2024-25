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
Nova::Doinker doinker = Nova::Doinker();
Nova::Auton auton = Nova::Auton(chassis, intake, clamp);

/**
 * @brief Initialize
 * 
 */
void initialize() {
    //pros::lcd::initialize();
    brain.initialize();

    chassis.initialize();
    chassis.calibrate();

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
    chassis.calibrate();

    intake.initialize();

    autonomous();
}

/**
 * @brief Autonomous
 * 
 */
void autonomous() {
    auton.blue1Elims();
    // Nova::moveToPos(10.0, 10.0, M_PI / 2.0); // 10 cm, 10 cm, 90 degrees
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
        doinker.run();

        pros::delay(10);
    }
}