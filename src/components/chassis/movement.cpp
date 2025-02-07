/**
 * \file movement.cpp
 *
 * \brief Contains Chassis movement in autonomous
 * 
 * \date Updated - 1/6/2025
 */

#include "globals.h"

#include "components/chassis.h"

float distanceBetweenPoints(const Point &a, const Point &b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float calculateCurvature(const Point &prev, const Point &curr, const Point &next) {
    float angle1 = atan2(curr.y - prev.y, curr.x - prev.x);
    float angle2 = atan2(next.y - curr.y, next.x - curr.x);

    return (angle2 - angle1);
}

/**
 * @brief Convert from inches to ticks
 * 
 * @param inches 
 * @return float 
 */
float inchesToTicks(float inches) {
    // Formula: Number of ticks in one inch = drive RPM / circumference of drive wheel
    return inches * (450 / (M_PI * 3.25));
}

/**
 * @brief Convert from ticks to inches
 * 
 * @param ticks 
 * @return float 
 */
float ticksToInches(float ticks) {
    // Formula: Number of inches in one tick = circumference of drive wheel / drive RPM
    return ticks * ((M_PI * 3.25) / 450);
}

int dirToSpin(double target,double currHeading)
{
    double d = (target - currHeading);
    double diff = d < 0 ? d + 360 : d;
    return(diff > 180 ? 1 : -1);
}

double minError(double target, double current)
{
    double b = std::max(target,current);
    double s = std::min(target,current);
    double diff = b - s;
    
    return((diff <= 180 ? diff : (360-b) + s) * dirToSpin(target, current));
}

double sign(double a)
{
    return(a > 0 ? 1 : -1);
}

/**
 * @brief Translate the Robot in x or y directions
 *
 * @param dist //inches

void Nova::Chassis::translate(float dist) {
    Nova::PID chassisPID = Nova::PID(
        5.75, // kp
        4,  // ki
        55, // kd increasing this will make more smooth
        0, // max cumulative error inches
        10,  // settle error inchjes
        100 // settle time MILLIS
    );
    // 2pir * rpm  * 1m = distance
    // ticks / (300 / 2pir) = inches travelled
    this -> resetMotorEncoders();

    float targetPosition = dist; // dist * 300/2pir

    float targetAngle = this -> getIMURotation();

    float kIMU = 5;
    float angleError = 0.0;
    float imuCorrection = 0.0;
    float chassisPower = 0.0;

    while (!(chassisPID.isSettled())) {
        float chassisError = targetPosition - ticksToInches((Nova::backLeft.get_position() + Nova::backRight.get_position()) / 2);

        float chassisOutput = chassisPID.compute(chassisError, true);

        angleError = targetAngle - this -> getIMURotation();

        imuCorrection = kIMU * angleError;

        chassisPID.checkIfSettled(targetPosition - ticksToInches((Nova::backLeft.get_position() + Nova::backRight.get_position()) / 2));

        chassisPower = chassisOutput > 120 ? 120 : (chassisOutput < -120 ? -120 : chassisOutput);

        //ctr.print(0, 0, "%0.2f", this -> chassis.getIMURotation());

        if (dist > 0.0) {
            Nova::leftDrive.move((chassisPower + imuCorrection) * 0.985);
            Nova::rightDrive.move((chassisPower - imuCorrection) * 1.015);
        } else {
            Nova::leftDrive.move((chassisPower + imuCorrection) * 0.935);
            Nova::rightDrive.move((chassisPower - imuCorrection) * 0.935);
        }

        pros::delay(10);
    }

    drive.brake();

    chassisPID.reset();

    // Nova::ctr.print(0, 0, "%0.2f", chassis.getIMURotation());
}

void Nova::Chassis::rotate(float angle) {
    Nova::PID turnPID = Nova::PID(
        2,  // kp
        4,  // ki
        7, // kd
        0, // max cumulative error inches
        5,  // settle error inchjes
        200 // settle time MILLIS
    );

    float targetPosition = this -> getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> getIMURotation();

        float power = turnPID.compute(error, false);

        Nova::ctr.print(0, 0, "%0.2f", error);

        turnPID.checkIfSettled(error);

        float chassisPower = power > 120 ? 120 : (power < -120 ? -120 : power);

        Nova::leftDrive.move(chassisPower);
        Nova::rightDrive.move(-chassisPower);

        pros::delay(10);
    }

    drive.brake();

    turnPID.reset();
}
*/

void Nova::Chassis::driveAngle(double targetDistance, double targetHeading, double timeout, bool resetSensors = true, double rushErrorThreshold = -1, double slewRate = -1)
{
    int startTime = pros::millis();

    Nova::PID chassisPID = Nova::PID(
        5.75, // kp
        4,  // ki
        55, // kd increasing this will make more smooth
        0, // tolerance
        10,  // integralshreshold
        100 // max integral
    );

     Nova::PID turnPID = Nova::PID(
        2,  // kp
        4,  // ki
        7, // kd
        0, // tolerance
        10,  // integralshreshold
        100 // max integral
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

    while (isRunning)
    {
        currentHeading = this -> getIMURotation();
        double angularError = minError(targetHeading, currentHeading);
        linearError = targetDistance - this -> getAvgEncoderValue();

        if (std::abs(angularError) < angleTolerance)
        {
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
}