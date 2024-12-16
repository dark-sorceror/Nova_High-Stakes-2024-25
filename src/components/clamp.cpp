/**
 * \file clamp.cpp
 *
 * \brief Contains clamp logic
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include "globals.h"

#include "components/clamp.h"

bool clampToggle = false;

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