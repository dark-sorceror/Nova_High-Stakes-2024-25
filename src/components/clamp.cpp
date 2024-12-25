/**
 * \file clamp.cpp
 *
 * \brief Contains clamp logic
 * 
 * \date Updated - 12/25/2024
 */

#include "globals.h"

#include "components/clamp.h"

bool clampToggle = false;

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
    if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        clampToggle = !clampToggle;

        clamp.set_value(clampToggle);
    }
}