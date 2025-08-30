/**
 * \file intake.cpp
 *
 * \brief Contains intake logic
 * 
 * \date Updated - 2/07/2025
 */

#include "components/intake.h"

bool intakeRaised = false;

/**
 * @brief Initialize Intake
 * 
 */
void Nova::Intake::initialize() {
    Nova::intake.tare_position();
    colorCheck.set_led_pwm(75);
}

void Nova::Intake::start(int voltage) {
    Nova::intake.move_voltage(voltage);
}

void Nova::Intake::stop() {
    Nova::intake.move_voltage(0);
}

void Nova::Intake::raiseIntake() {
    Nova::intakePiston.set_value(1);
}

void Nova::Intake::lowerIntake() {
    Nova::intakePiston.set_value(0);
}

/**
 * @brief Run Intake
 * 
 */
void Nova::Intake::run() {         
    // RED ALLIANCE: colorCheck.get_hue() > 130 && colorCheck.get_hue() < 210 && colorCheck.get_proximity() > 240
    // BLUE ALLIANCE: colorCheck.get_hue() > 5 && colorCheck.get_hue() < 40 && colorCheck.get_proximity() > 240
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) Nova::intake.move(107);
    else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) Nova::intake.move(-107);
    else Nova::intake.brake();
}