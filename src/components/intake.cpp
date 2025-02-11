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
    optical.set_led_pwm(75);
}

void Nova::Intake::start(int voltage) {
    Nova::intake.move_voltage(voltage);
}

void Nova::Intake::stop() {
    Nova::intake.move_voltage(0);
}

void Nova::Intake::extendGoalRush() {
    Nova::raiseIntake.set_value(1);
}

void Nova::Intake::retractGoalRush() {
    Nova::raiseIntake.set_value(0);
}

/**
 * @brief Run Intake
 * 
 */
void Nova::Intake::run() {         
    // RED ALLIANCE: optical.get_hue() > 130 && optical.get_hue() < 210 && optical.get_proximity() > 240
    // BLUE ALLIANCE: optical.get_hue() > 5 && optical.get_hue() < 40 && optical.get_proximity() > 240
    if (optical.get_hue() > 5 && optical.get_hue() < 40 && optical.get_proximity() > 240) {
        pros::Task colorSortLogic([] {
            Nova::colorSort.set_value(1);
            pros::delay(500);
            Nova::colorSort.set_value(0);
        });
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) Nova::intake.move(92);
    else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) Nova::intake.move(-92);
    else Nova::intake.brake();
}