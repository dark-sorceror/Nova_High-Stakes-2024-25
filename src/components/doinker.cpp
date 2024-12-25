/**
 * \file doinker.cpp
 *
 * \brief Contains doinker logic
 * 
 * \date Updated - 12/25/2024
 */

#include "globals.h"

#include "components/doinker.h"

bool donkerToggle = false;

void Nova::Doinker::up() {
    Nova::clamp.set_value(0);
}

void Nova::Doinker::down() {
    Nova::clamp.set_value(1);
}

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