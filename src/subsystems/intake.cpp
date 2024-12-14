/**
 * \file intake.cpp
 *
 * \brief Contains intake logic
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#include "main.h"

bool sortToggle = true;
bool lock = false;

/**
 * @brief Initialize Intake
 * 
 */
void Nova::Intake::initialize() {
    Nova::intake.tare_position();
}

void Nova::Intake::outTakeTask() {
    lock = true;
    Nova::intake.move(115);
    pros::delay(700);
    Nova::intake.brake();
    lock = false;
}

void Nova::Intake::colorSort() {
    pros::Task([] {
        uint32_t lastMoveTime = 0;  // Store the last time the motor was moved
        uint32_t delayTime = 1000; 
        
 		while (true) {
            uint32_t currentTime = pros::millis();
            
 			if (optical.get_hue() > 100 && optical.get_hue() < 200 && lock == false) {
                
                if (currentTime - lastMoveTime > delayTime) {
                    Nova::intake.move(80);  // Move intake
                    lastMoveTime = currentTime;  // Update the last move time
                }
 			}
            /*
 			if (alliance == "blue" && optical.get_hue() > 15 && optical.get_hue() < 40 && lock == false && sortToggle == true) {
 				raiseHoodTask();
 			}
            */
		
 			if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
     			sortToggle = !sortToggle;
 				optical.set_led_pwm((sortToggle == true ? 75 : 0)); // Turn off LED if not sorting
     		}
 		}
 	});
}

/**
 * @brief Run Intake
 * 
 */
void Nova::Intake::run() {
    if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        Nova::intake.move(-115);
    } else if (ctr.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        Nova::intake.move(115);
    } else {
        Nova::intake.brake();
    }
}