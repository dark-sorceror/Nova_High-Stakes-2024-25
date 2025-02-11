/**
 * \file clamp.cpp
 *
 * \brief Contains clamp logic
 * 
 * \date Updated - 1/6/2025
 */

#include "components/clamp.h"

bool clampToggle = false;
bool clampJustReleased = false;

void Nova::Clamp::lock() {
    Nova::clamp.set_value(1);
}

void Nova::Clamp::unlock() {
    Nova::clamp.set_value(0);
}

/**
 * @brief Run clamp
 *
 */
void Nova::Clamp::run() {
    if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::Task clampLogic([] {
            clampToggle = !clampToggle;
            Nova::clamp.set_value(clampToggle);
    
            clampJustReleased = true;
            
            pros::delay(1000); // delay to leave the unclamped stake before it is registered as a clamp again
    
            clampJustReleased = false;
        });
    }

    if (clampCheck.get_distance() <= 50 && !clampToggle && !clampJustReleased) {
        clampToggle = true;
        pros::delay(500);
        clamp.set_value(true);
    }
}