/**
 * \file auton.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 
 */ 

#include "PID.h"
#include "globals.h"
#include "auton.h"
#include "pros/rtos.hpp"
#include <iostream>
#include <map>
#include <list>

/*
1800 ticks/rev with 36:1 gears red
900 ticks/rev with 18:1 gears green
300 ticks/rev with 6:1 gears blue

144 inches x 144 inches field
omni wheel circumference =  2pi 3.25 inch = 20.42 inches / rev
*/

Nova::Auton::Auton(Drive drive, Intake intake):
    drive(drive),
    intake(intake)
{};
// dist = inches
void Nova::Auton::translate(float dist) {
    PID drivePID = PID(
        0, 
        1, 
        0.01, 
        5, 
        250, 
        50, 
        250, 
        5000
    );

    PID turnPID = PID(
        0, 
        4, 
        0.0, 
        1, 
        250
    );

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = drive.getIMURotation();
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 4, MIN_STALL_TIME = 400;

    while (!(drivePID.isSettled())) {
        float driveError = targetPosition - this -> drive.getAvgEncoderValue();
        float turnError = targetAngle - drive.getIMURotation();

        float driveOutput = drivePID.compute(driveError);
        float turnOutput = turnPID.compute(turnError);

        float drivePower = driveOutput > 120 ? 120 : (driveOutput < -120 ? -120 : driveOutput);
        float turnPower = turnOutput > 120 ? 120 : (turnOutput < -120 ? -120 : turnOutput);

        Nova::leftDrive.move(drivePower + turnPower);
        Nova::rightDrive.move(drivePower - turnPower);

        pros::delay(10);

        if (drivePower > MIN_STALL_POWER && this -> drive.getAvgVelocity() < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }

    drivePID.reset();
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
    
    float targetPosition = this -> drive.getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> drive.getIMURotation();
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
        float error = angle - this -> drive.getIMURotation();
        float power = turnPID.compute(error);

        Nova::leftDrive.move(power);
        Nova::rightDrive.move(-power);

        pros::delay(10);
    }

    turnPID.reset();
}

void Nova::Auton::swerveRight(float dist, float angle) {
    PID drivePID = PID(
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

    ctr.print(0, 0, "%f", drive.getIMURotation());

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = drive.getIMURotation();
    float targetSwerveAngle = drive.getIMURotation() - angle;
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 10, MIN_STALL_TIME = 400;

    while (!(swingPID.isSettled())) {
        float driveError = targetPosition - this-> drive.getAvgEncoderValue();
        float turnError = targetAngle - this-> drive.getIMURotation();
        float swerveError = targetSwerveAngle - this->drive.getIMURotation();

        float driveOutput = drivePID.compute(driveError);
        float turnOutput = turnPID.compute(turnError);
        float swerveOutput = swingPID.compute(swerveError);
        
        float drivePower = driveOutput > 500 ? 500 : driveOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;
        float swervePower = swerveOutput > 500 ? 500 : swerveOutput;

        Nova::leftDrive.move(drivePower + turnPower);
        Nova::rightDrive.move(drivePower - turnPower - swervePower);

        pros::delay(10);

        if (fabs(drivePower) < MIN_STALL_POWER && fabs(this -> drive.getAvgVelocity()) < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }
    
    Nova::drive.brake();
    drivePID.reset();
    turnPID.reset();
    swingPID.reset();
}

void Nova::Auton::swerveLeft(float dist, float angle) { 
     PID drivePID = PID(
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

    ctr.print(0, 0, "%f", drive.getIMURotation());

    this -> drive.resetMotorEncoders();

    float targetPosition = dist * 46.28245103; // dist * 300/2pir
    float targetAngle = drive.getIMURotation();
    float targetSwerveAngle = drive.getIMURotation() + angle;
    float timeSpentStalled = 0;
    const float MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 10, MIN_STALL_TIME = 400;

    while (!(swingPID.isSettled())) {
        float driveError = targetPosition - this-> drive.getAvgEncoderValue();
        float turnError = targetAngle - this-> drive.getIMURotation();
        float swerveError = targetSwerveAngle - this->drive.getIMURotation();

        float driveOutput = drivePID.compute(driveError);
        float turnOutput = turnPID.compute(turnError);
        float swerveOutput = swingPID.compute(swerveError);
        
        float drivePower = driveOutput > 500 ? 500 : driveOutput;
        float turnPower = turnOutput > 500 ? 500 : turnOutput;
        float swervePower = swerveOutput > 500 ? 500 : swerveOutput;

        Nova::leftDrive.move(drivePower + turnPower + swervePower);
        Nova::rightDrive.move(drivePower - turnPower);

        pros::delay(10);

        if (fabs(drivePower) < MIN_STALL_POWER && fabs(this -> drive.getAvgVelocity()) < MIN_STALL_VELOCITY) timeSpentStalled += 10;
        else timeSpentStalled = 0;

        if (timeSpentStalled > MIN_STALL_TIME) break;
    }
    
    Nova::drive.brake();
    drivePID.reset();
    turnPID.reset();
    swingPID.reset();
}

void Nova::Auton::test() {
    this->translate(24);
}