/**
 * \file auton.cpp
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#include "auton.h"
#include "globals.h"

#include "Subsystems/Chassis/chassis.h"
#include "Subsystems/intake.h"
#include "Subsystems/clamp.h"

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

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

/**
 * @brief Translate the Robot in x or y directions
 * 
 * @param dist 
 */
void Nova::Auton::translate(float dist) {
    Nova::PID chassisPID = Nova::PID(
        0, 
        1, 
        0.01, 
        5, 
        250, 
        50, 
        250, 
        5000
    );

    Nova::PID turnPID = Nova::PID(
        0, 
        4, 
        0.0, 
        1, 
        250
    );

    this -> chassis.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = chassis.getIMURotation();
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 4, MIN_STALL_TIME = 400;

    while (!(chassisPID.isSettled())) {
        float chassisError = targetPosition - this -> chassis.getAvgEncoderValue();
        float turnError = targetAngle - chassis.getIMURotation();

        float chassisOutput = chassisPID.compute(chassisError);
        float turnOutput = turnPID.compute(turnError);

        float chassisPower = chassisOutput > 120 ? 120 : (chassisOutput < -120 ? -120 : chassisOutput);
        float turnPower = turnOutput > 120 ? 120 : (turnOutput < -120 ? -120 : turnOutput);

        Nova::leftDrive.move(chassisPower + turnPower);
        Nova::rightDrive.move(chassisPower - turnPower);

        pros::delay(10);

        if (chassisPower > MIN_STALL_POWER && this -> chassis.getAvgVelocity() < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    chassisPID.reset();
    turnPID.reset();
}

/**
 * @brief Rotate the Robot in 360 degree directions
 * 
 * @param angle 
 */
void Nova::Auton::rotate(float angle) {
    PID turnPID = PID(
        0, 
        4.75, 
        0.0, 
        28, 
        250, 
        5, 
        250, 
        3000
    );
    
    float targetPosition = this -> chassis.getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> chassis.getIMURotation();
        float power = turnPID.compute(error);

        Nova::leftDrive.move(power);
        Nova::rightDrive.move(-power);

        pros::delay(10);
    }

    turnPID.reset();
}

/**
 * @brief Rotate the Robot in a 360 degree direction with 90 to North
 * 
 * @param angle 
 */
void Nova::Auton::rotateAbsolute(float angle) {
    PID turnPID = PID(
        0, 
        4.75, 
        0.0, 
        28.0, 
        100, 
        5, 
        500, 
        3000
    );

    while (!(turnPID.isSettled())) {
        float error = angle - this -> chassis.getIMURotation();
        float power = turnPID.compute(error);

        Nova::leftDrive.move(power);
        Nova::rightDrive.move(-power);

        pros::delay(10);
    }

    turnPID.reset();
}

/**
 * @brief Blue 1 Auton Elim
 * 
 */
void Nova::Auton::blue1Elims() {
    this -> translate(24);
}