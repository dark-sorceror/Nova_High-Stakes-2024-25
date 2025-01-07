/**
 * \file auton.cpp
 *
 * \brief Contains autonomous paths
 * 
 * \date Updated - 1/6/2025
 */

#include "auton.h"

void Nova::Auton::test() {
    clamp.lock();
    intake.start();
    chassis.translate(96);
    chassis.rotate(90);
    chassis.translate(96);
    clamp.unlock();
    intake.stop();
}