/**
 * \file ladyBrown.cpp
 *
 * \brief Contains lady brown logic
 *
 * \date Updated - 2/10/2025
 */

#include "components/ladyBrown/ladyBrown.h"
#include "components/ladyBrown/states.h"

const int numWallStakeStates = 2;
double wallStakeStates[numWallStakeStates] = {181.5, 197};

int currState = 0;
double target = 181.5;

bool manual = false;

bool intakea = false;
bool finished = false;

double targetPos = Nova::intake.get_position();

Nova::State* Nova::State::instance = nullptr;

Nova::LadyBrownState Nova::State::getLadyBrownState()  {
    mutex.take();
    auto returnVal = LadyBrownState;
    mutex.give();
    return returnVal; 
}

void RobotState::setLiftState(LiftState state) {
    mutex.take();
    liftState = state;
    mutex.give();
}

void Nova::LadyBrown::goToPosition(float position) {
    target = position;
}

/*
void nextWallStakeState() {
    currState += 1;

   if (currState == 2) currState = 0;

    target = wallStakeStates[currState];
}
*/

void Nova::LadyBrown::setState(LadyBrownState state) {
    currentState = state;
    setTarget(currentState);
    auto s = RobotState::getInstance();
    s->setLadyBrownState(currentState);
}

void Nova::LadyBrown::next() {
    setState(fwdMap[currentState]);
}

void Nova::LadyBrown::prev() {
    setState(revMap[currentState]);
}

void Nova::LadyBrown::setTarget(LadyBrownState state) {
    target = valueMap[state];
}

void Nova::LadyBrown::startControl() {
    if (task == nullptr) { // check for background tasks
        calibrate();

        motor -> set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        task = new pros::Task{[this] {
            while (true) {
                control();

                pros::delay(10);
            }
        }};
    } else {
        calibrate();
    }
    
    pros::delay(20);
}

void Nova::LadyBrown::calibrate() {
    double current = motor -> get_current_draw();
    pros::delay(100);
    motor -> move(-70);
    pros::delay(100);

    while (current < 980) {
        current = motor -> get_current_draw();
        pros::delay(10);
    }

    motor -> tare_position();
    motor -> move(0);

}

void control() {
    double error = target - round(Nova::lbCheck.get_angle() / 100);
    double kp = 3;
    double velocity = kp * error;

    float power = velocity > 127 ? 127 : (velocity < -127 ? -127 : velocity);

    if (Nova::lbCheck.get_angle() != target) {
        Nova::lb.move(power);
    }
}

void intakeControl() {
    double currentPos = Nova::intake.get_position();
    double previousPos;
    double target = currentPos + 10;

    if (currentPos != target && previousPos != currentPos) {
        Nova::intake.move(50);
    } else {
        previousPos = currentPos;
    }
}

void Nova::LadyBrown::initialize() {
    pros::Task liftControlTask([] {
        while (true) {
            if (!manual) {
                control();
            }
            if(intakea) {
                intakeControl();
            } 

            pros::delay(10);
        } 
    });
}

void Nova::LadyBrown::spin(double voltage) {
    if (off) {
        motor->move(voltage);

        if (voltage == 0 && (abs(motor->get_position() - target) <= snapRange)) {
            off = false; // snapping back into control mode
        }
    }
}

void Nova::LadyBrown::run() {
    if (Nova::ctr.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        manual = false;
        nextWallStakeState();
    }
    
    if (Nova::ctr.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        manual = true;
        intakea = true;

        lb.move(127);
    } else if (Nova::ctr.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        manual = true;

        lb.move(-127);
    } else {
        manual = false;
        intakea = false;
    }
}