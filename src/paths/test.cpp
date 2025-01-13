/**
 * \file auton.cpp
 *
 * \brief Contains autonomous paths
 * 
 * \date Updated - 1/6/2025
 */

#include "auton.h"

/**
 * @brief Construct a new Nova::Auton::Auton object
 *
 * @param chassis
 * @param intake
 * @param clamp
 */
Nova::Auton::Auton(
    Nova::Chassis chassis,
    Nova::Intake intake,
    Nova::Clamp clamp
): 
    chassis(chassis),
    intake(intake),
    clamp(clamp) 
{};

void Nova::Auton::test() {
    clamp.lock();
    intake.start();
    chassis.translate(96);
    chassis.rotate(90);
    chassis.translate(96);
    clamp.unlock();
    intake.stop();
}