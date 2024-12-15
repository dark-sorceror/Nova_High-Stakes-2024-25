/**
 * \file auton.cpp
 *
 * Updated - 1/13/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "subsystems/Chassis/chassis.h"
#include "subsystems/intake.h"
#include "subsystems/clamp.h"
#include "auton.h"
#include "globals.h"

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

Nova::Auton::Auton(Nova::Chassis chassis, Nova::Intake intake, Nova::Clamp clamp):
    chassis(chassis),
    intake(intake),
    clamp(clamp)
{};

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

void Nova::Auton::swerveRight(float dist, float angle) {
    PID chassisPID = PID(
        0, 
        1.5, 
        0.0, 
        8.5, 
        250, 
        50, 
        250, 
        5000
    );

    PID turnPID = PID(
        0, 
        0.1, 
        0.0, 
        1, 
        100
    );

    PID swingPID = PID(
        0, 
        3.0, 
        0.0, 
        2.0, 
        250,
        50, 
        250, 
        5000
    );

    this -> chassis.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = chassis.getIMURotation();
    float targetSwerveAngle = chassis.getIMURotation() - angle;
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 10, MIN_STALL_TIME = 400;

    while (!(swingPID.isSettled())) {
        float chassisError = targetPosition - this-> chassis.getAvgEncoderValue();
        float turnError = targetAngle - this-> chassis.getIMURotation();
        float swerveError = targetSwerveAngle - this->chassis.getIMURotation();

        float chassisOutput = chassisPID.compute(chassisError);
        float turnOutput = turnPID.compute(turnError);
        float swerveOutput = swingPID.compute(swerveError);
        
        float chassisPower = chassisOutput > 500 ? 500 : chassisOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;
        float swervePower = swerveOutput > 500 ? 500 : swerveOutput;

        Nova::leftDrive.move(chassisPower + turnPower);
        Nova::rightDrive.move(chassisPower - turnPower - swervePower);

        pros::delay(10);

        if (fabs(chassisPower) < MIN_STALL_POWER && fabs(this -> chassis.getAvgVelocity()) < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }
    
    Nova::drive.brake();
    chassisPID.reset();
    turnPID.reset();
    swingPID.reset();
}

void Nova::Auton::swerveLeft(float dist, float angle) { 
     PID chassisPID = PID(
        0, 
        1.5, 
        0.0, 
        8.5, 
        250, 
        50, 
        250, 
        5000
    );

    PID turnPID = PID(
        0, 
        0.1, 
        0.0, 
        1, 
        100
    );

    PID swingPID = PID(
        0, 
        3.0, 
        0.0, 
        2.0, 
        250,
        50, 
        250, 
        5000
    );

    this -> chassis.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = chassis.getIMURotation();
    float targetSwerveAngle = chassis.getIMURotation() + angle;
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 10, MIN_STALL_TIME = 400;

    while (!(swingPID.isSettled())) {
        float chassisError = targetPosition - this-> chassis.getAvgEncoderValue();
        float turnError = targetAngle - this-> chassis.getIMURotation();
        float swerveError = targetSwerveAngle - this->chassis.getIMURotation();

        float chassisOutput = chassisPID.compute(chassisError);
        float turnOutput = turnPID.compute(turnError);
        float swerveOutput = swingPID.compute(swerveError);
        
        float chassisPower = chassisOutput > 500 ? 500 : chassisOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;
        float swervePower = swerveOutput > 500 ? 500 : swerveOutput;

        Nova::leftDrive.move(chassisPower + turnPower + swervePower);
        Nova::rightDrive.move(chassisPower - turnPower);

        pros::delay(10);

        if (fabs(chassisPower) < MIN_STALL_POWER && fabs(this -> chassis.getAvgVelocity()) < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }
    
    Nova::drive.brake();
    chassisPID.reset();
    turnPID.reset();
    swingPID.reset();
}

void Nova::Auton::blue1Elims() {
    this -> translate(24);
}