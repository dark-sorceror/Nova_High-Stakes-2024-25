/**
 * \file intake.cpp
 *
 * \brief Contains intake logic
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#include "main.h"

/**
 * @brief Initialize Intake
 * 
 */
void Nova::Intake::initialize() {
    Nova::intake.tare_position();
    Nova::conveyor.tare_position();
}

/**
 * @brief Run Intake
 * 
 */
void Nova::Intake::run() {
    if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        Nova::intake.move(-115);
        Nova::conveyor.move(115);
    } else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        Nova::intake.move(115);
        Nova::conveyor.move(-115);
    } else {
        Nova::intake.brake();
        Nova::conveyor.brake();
    }
}