/**
 * \file intake.cpp
 *
 * \brief Contains intake logic
 * 
 * \date Updated - 12/25/2024
 */

#include "globals.h"

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
    // RED ALLIANCE: optical.get_hue() > 130 && optical.get_hue() < 210 && optical.get_proximity() > 240
    // BLUE ALLIANCE: optical.get_hue() > 5 && optical.get_hue() < 40 && optical.get_proximity() > 240

    if (optical.get_hue() > 5 && optical.get_hue() < 40 && optical.get_proximity() > 240) Nova::intake.move(127);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) Nova::intake.move(-100);
    else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) Nova::intake.move(100);
    else Nova::intake.brake();
}