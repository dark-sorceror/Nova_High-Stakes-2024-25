/**
 * \file doinker.cpp
 *
 * \brief Contains doinker logic
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#include "main.h"

bool donkerToggle = false;

/**
 * @brief Run doinker
 *
 */
void Nova::Doinker::run() {
    if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        donkerToggle = !donkerToggle;

        doinker.set_value(donkerToggle);
    }
}