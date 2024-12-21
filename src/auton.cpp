/**
 * \file auton.cpp
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#include "globals.h"

#include "pid.h"
#include "auton.h"

#include "components/chassis/chassis.h"
#include "components/intake.h"
#include "components/clamp.h"

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
 * @param dist //inches
 */
void Nova::Auton::translate(float dist) {
    Nova::PID chassisPID = Nova::PID(
        1, //kp
        0, // ki
        12, // kd
        10, // max cumulative error inches
        5, // settle error inchjes
        100 // settle time MILLIS
    );

    this -> chassis.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir

    while (!(chassisPID.isSettled())) {
        float chassisError = targetPosition - Nova::backLeft.get_position();

        float chassisOutput = chassisPID.compute(chassisError);

        chassisPID.checkIfSettled(dist - (Nova::backLeft.get_position() / 46.28245103));

        float chassisPower = chassisOutput > 120 ? 120 : (chassisOutput < -120 ? -120 : chassisOutput);

        Nova::leftDrive.move(chassisPower);
        Nova::rightDrive.move(chassisPower);

        pros::delay(10);
    }

    chassisPID.reset();

    //Nova::ctr.print(0, 0, "%0.2f", chassis.getIMURotation());
}

void Nova::Auton::rotate(float angle) {
    Nova::PID turnPID = Nova::PID(
        1, //kp
        0, // ki
        0, // kd
        110, // max cumulative error degrees
        10, // settle error degrees
        100 // settle time MILLIS
    );
    
    float targetPosition = this -> chassis.getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> chassis.getIMURotation();

        float power = turnPID.compute(error);

        turnPID.checkIfSettled(error);

        float chassisPower = power > 120 ? 120 : (power < -120 ? -120 : power);

        Nova::leftDrive.move(chassisPower);
        Nova::rightDrive.move(-chassisPower);

        pros::delay(10);
    }

    turnPID.reset();
}

void Nova::Auton::blue1Elims() {
    this -> translate(24);
    this -> rotate(90);
    this -> translate(-24);
    this -> rotate(90);
    this -> translate(24);
    this -> rotate(180);
}