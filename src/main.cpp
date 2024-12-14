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
Nova::Chassis drive = Nova::Chassis();
Nova::Intake intake = Nova::Intake();
Nova::Clamp clamp = Nova::Clamp();

/**
 * @brief Initialize
 * 
 */
void initialize() {
    //pros::lcd::initialize();
    brain.initialize();

    drive.initialize();
    drive.calibrate();

    lv_task_handler();
}

void disabled() {}

/**
 * @brief Competition Initialize
 * 
 */
void competition_initialize() {
    brain.initialize();

    drive.initialize();
    drive.calibrate();

    lv_task_handler();

    autonomous();
}

/**
 * @brief Autonomous
 * 
 */
void autonomous() {
    // Nova::moveToPos(10.0, 10.0, M_PI / 2.0); // 10 cm, 10 cm, 90 degrees
}

/**
 * @brief User Control
 * 
 */
void opcontrol() {
    while (true) {
        Nova::update(); // tracking algorithm loop

        drive.run();

        pros::delay(10);
    }
}