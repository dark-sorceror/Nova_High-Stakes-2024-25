/**
 * \file intake.cpp
 *
 * \brief Contains intake logic
 * 
 * \date Updated - 1/6/2025
 */

#include "components/intake.h"

/**
 * @brief Initialize Intake
 * 
 */
void Nova::Intake::initialize() {
    Nova::intake.tare_position();
    optical.set_led_pwm(75);
}

void Nova::Intake::start() {
    Nova::intake.move_voltage(-12000);
}

void Nova::Intake::stop() {
    Nova::intake.move_voltage(0);
}

/**
 * @brief Run Intake
 * 
 */
void Nova::Intake::run() {   
    ctr.print(0, 0, "%.2f", intake.get_actual_velocity());                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) Nova::intake.move(-80);
}