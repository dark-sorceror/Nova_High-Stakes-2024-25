/**
 * \file ladyBrown.cpp
 *
 * \brief Contains lady brown logic
 * 
 * \date Updated - 1/20/2025
 */

#include "components/ladyBrown.h"

const int numStates = 5;
double states[numStates] = {138, 171, 182, 310, 359};
int currState = 0;
double target = 138;

void nextState() {
    currState += 1;

    if (currState == 3) {
        pros::Task shootReturn([]{
            target = states[currState];
            pros::delay(500);
            currState = 1;

            target = states[currState] + 1.5;
        });
    } else {
        target = states[currState];
    }
}

void liftControl() {
    double error = target - round(Nova::lbCheck.get_angle()/100);
    double kp = 1.55;
    double velocity = kp * error;

    float power = velocity > 30 ? 30 : (velocity < -30 ? -30 : velocity);

    if (Nova::lbCheck.get_angle() != target) {
        Nova::lb1.move(power);
        Nova::lb2.move(-power);
    }
}

void Nova::LadyBrown::initialize() {
    pros::Task liftControlTask([]{
        while (true) {
            liftControl();
            pros::delay(10);
        }
    });

    nextState();
}

void Nova::LadyBrown::run() {
    while (true) {
        if (Nova::ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
			nextState();
		}

	    pros::delay(20);
    }
}