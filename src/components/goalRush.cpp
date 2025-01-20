/**
 * \file goalRush.cpp
 *
 * \brief Contains goal rush logic
 * 
 * \date Updated - 1/20/2025
 */

#include "components/goalRush.h"

bool goalRushToggle = false;

void Nova::GoalRush::up() {
    Nova::goalRush.set_value(0);
}

void Nova::GoalRush::down() {
    Nova::goalRush.set_value(1);
}

/**
 * @brief Run goalRush
 *
 */
void Nova::GoalRush::run() {
    if (ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        goalRushToggle = !goalRushToggle;

        goalRush.set_value(goalRushToggle);
    }
}