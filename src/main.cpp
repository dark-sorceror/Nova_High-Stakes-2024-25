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

Nova::Auton auton = Nova::Auton(chassis, intake, clamp);

/**
 * @brief Initialize
 * 
 */
void initialize() {
    pros::lcd::initialize();
    
    brain.initialize();
    chassis.initialize();
    intake.initialize();

    Nova::lbCheck.reset();
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
}

/**
 * @brief Autonomous
 * 
 */
void autonomous() {
}

/**
 * @brief User Control
 * 
 */
void opcontrol() {
    Nova::lbCheck.reset();
    Nova::lbCheck.reset_position();

    while (true) {
        chassis.updatePosition(); // tracking algorithm loop

        chassis.run();
        intake.run();
        clamp.run();
        ladyBrown.run();

        //Nova::ctr.print(0, 0, "%0.2f", chassis.getIMURotation());

        pros::delay(10);
    }
}