/**
 * \file ladyBrown.cpp
 *
 * \brief Contains lady brown logic
 *
 * \date Updated - 2/10/2025
 */

#include "components/ladyBrown.h"

const int numWallStakeStates = 5;
double wallStakeStates[numWallStakeStates] = {132, 150, 170, 250, 350};

const int numAllianceStakeStates = 5;
double allianceStakeStates[numAllianceStakeStates] = {132, 150, 170, 300, 350};

int currState = 0;
double target = 132;

void Nova::LadyBrown::goToPosition(int position) {
    target = position;
}

void nextWallStakeState() {
    currState += 1;

    if (currState == 4) {
        pros::Task shootReturn([] {
            target = wallStakeStates[currState];
            pros::delay(500);
            currState = 1;
 
            target = wallStakeStates[currState] + 1.5; 
        });
    } else {
        target = wallStakeStates[currState];
    }
}

void nextAllianceStakeStates() {
    currState += 1;

    if (currState == 4) {
        pros::Task shootReturn([] {
            target = allianceStakeStates[currState];
            pros::delay(500);
            currState = 1;

            target = allianceStakeStates[currState] + 1.5; 
        });
    } else {
        target = allianceStakeStates[currState];
    }
}

void liftControl() {
    double error = target - round(Nova::lbCheck.get_angle() / 100);
    double kp = 2.5;
    double velocity = kp * error;

    float power = velocity > 127 ? 127 : (velocity < -127 ? -127 : velocity);

    if (Nova::lbCheck.get_angle() != target) {
        Nova::lb.move(power);
    }
}

void Nova::LadyBrown::initialize() {
    pros::Task liftControlTask([] {
        while (true) {
            liftControl();
            pros::delay(10);
        } 
    });

    nextWallStakeState();
}

void Nova::LadyBrown::run() {
    if (Nova::ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        nextWallStakeState();
    }

    if (Nova::ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        nextAllianceStakeStates();
    }

    pros::delay(20);
}