/**
 * \file main.cpp
 *
 * \brief Main file
 * 
 * \date Updated - 1/20/2025
 */

#include "main.h"

Nova::Brain brain = Nova::Brain();

Nova::Chassis chassis = Nova::Chassis();

Nova::Intake intake = Nova::Intake();

Nova::LadyBrown ladyBrown = Nova::LadyBrown();

Nova::Clamp clamp = Nova::Clamp();

Nova::Doinker doinker = Nova::Doinker();

Nova::Auton auton = Nova::Auton(chassis, intake, clamp, ladyBrown);

/**
 * @brief Initialize
 * 
 */
void initialize() {
    brain.initialize();
    chassis.initialize();
    intake.initialize();
    ladyBrown.initialize();
}

void disabled() {}

/**
 * @brief Competition Initialize
 * 
 */
void competition_initialize() {}

/**
 * @brief Autonomous
 * 
 */
void autonomous() {
    auton.test();
}

/**
 * @brief User Control
 * 
 */
void opcontrol() {
    while (true) {
       // chassis.updatePosition(); // tracking algorithm loop

        chassis.run();
        intake.run();
        clamp.run();
        ladyBrown.run();
        doinker.run();

        pros::delay(10);
    }
}