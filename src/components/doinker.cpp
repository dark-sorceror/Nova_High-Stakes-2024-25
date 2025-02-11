/**
 * \file doinker.cpp
 *
 * \brief Contains doinker logic
 * 
 * \date Updated - 1/6/2025
 */

#include "components/doinker.h"

bool donkerToggle = false;

void Nova::Doinker::extend() {
    Nova::doinker.set_value(1);
}

void Nova::Doinker::retract() {
    Nova::doinker.set_value(0);
}

/**
 * @brief Run doinker
 *
 */
void Nova::Doinker::run() {
    if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        donkerToggle = !donkerToggle;

        doinker.set_value(donkerToggle);
    }
}