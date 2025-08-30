/**
 * \file 2dpid.cpp
 *
 * \brief Contains Chassis movement in autonomous
 * 
 * \date Updated - 3/10/2025
 */

#include "globals.h"

#include "components/chassis.h"

#include "modules/controllers/velocity.h"

void Nova::Chassis::driveAngle(double targetDistance, double targetHeading, double timeout, bool resetSensors = true, double rushErrorThreshold = -1, double slewRate = -1) {
    // chassMutex.take();

    if (params.async) {
        params.async = false;
        pros::Task task([&]() { driveAngle(target, params);});
        pros::delay(10);
        return;
    }
        
    this -> waitUntilSettled();
    if (params.exit == nullptr) params.exit = new exit::Range(3, 20);
    moving = true;

    int startTime = pros::millis();

    Nova::PID chassisPID = Nova::PID(
        5,  // kp
        0,  // ki
        0,  // kd
        0,  // tolerance
        0,  // integralshreshold
        0   // max integral
    );

    Nova::PID chassisPID = Nova::PID(
        2.5,  // kp
        0,    // ki
        0,    // kd
        0,    // tolerance
        0,    // integralshreshold
        0     // max integral
    );
    
    double linearTolerance = 0;
    double angleTolerance = 0;

    double currentHeading = this -> getIMURotation();
    double directionSign = sign(targetDistance);
    double linearError = targetDistance;
    double previousLinearOutput = 0;
    bool isRunning = true;

    if (resetSensors) {
        this -> resetMotorEncoders();
    }

    while (isRunning) {
        currentHeading = this -> getIMURotation();
        double angularError = minError(targetHeading, currentHeading);
        linearError = targetDistance - this -> getAvgEncoderValue();

        if (std::abs(angularError) < angleTolerance) {
            angularError = 0;
        }

        double angularOutput = turnPID.compute(angularError);
        double linearOutput = chassisPID.compute(linearError);

        if (std::abs(linearOutput - previousLinearOutput) > slewRate && slewRate != -1) {
            linearOutput = previousLinearOutput + (sign(linearOutput - previousLinearOutput) * slewRate);
        }
        previousLinearOutput = linearOutput;

        if (std::abs(linearError) > std::abs(rushErrorThreshold) && rushErrorThreshold > 0) {
            linearOutput = 127 * sign(linearOutput);
        }

        if (std::abs(linearOutput) + std::abs(angularOutput) > 127)
        {
            linearOutput = (127 - std::abs(angularOutput)) * sign(linearOutput);
        }

        if (rushErrorThreshold > 0 && std::abs(linearError) < linearTolerance && std::abs(linearOutput) < 20) {
            break;
        }

        Nova::leftDrive.move(linearOutput - angularOutput);
        Nova::rightDrive.move(linearOutput + angularOutput);

        isRunning = pros::millis() - startTime <= timeout;

        if (rushErrorThreshold == 0) {
            isRunning = isRunning && std::abs(linearError) > linearTolerance;
        }
        pros::delay(10);
    }
    
    drive.brake();

    if (params.vMin != 0) drive.brake();
    moving = false;

    // chassMutex.give();
}