/**
 * \file movement.cpp
 *
 * \brief Contains Chassis movement in autonomous
 * 
 * \date Updated - 2/10/2025
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
*/
 // 5, 0, 50, 0, 10, 200 - 21.5 inches for 24 inches
    // 5.75, 0, 25, 0, 5, 200 - 12 for 12 inches

    // 5.85, 0, 40, 0, 5, 200 - 90 degrees for 90 degrees
    // 5.85, 0, 40, 0, 5, 200 - 45 degrees for 45 degrees
    // 5.5, 0, 40, 0, 5, 200 - 180 degrees for 180 degrees // 5, 0, 50, 0, 10, 200 - 21.5 inches for 24 inches
    // 5.75, 0, 25, 0, 5, 200 - 12 for 12 inches

    // 5.85, 0, 40, 0, 5, 200 - 90 degrees for 90 degrees
    // 5.85, 0, 40, 0, 5, 200 - 45 degrees for 45 degrees
    // 5.5, 0, 40, 0, 5, 200 - 180 degrees for 180 degrees
void Nova::Chassis::translate(float dist, int maxSpeed) {
    Nova::PID chassisPID = Nova::PID(0,0,0,0,0,0);
    if (fabsf(dist) >= 48) {
        chassisPID = Nova::PID(5.2, 0, 50, 0, 8, 150); 
    } else if (fabsf(dist) >= 24 && fabsf(dist) < 48) {
        chassisPID = Nova::PID(5.6, 0, 50, 0, 6, 150); 
    } else {
        chassisPID = Nova::PID(5.5, 0, 25, 0, 5, 150);
    }
    // 2pir * rpm  * 1m = distance
    // ticks / (300 / 2pir) = inches travelled
    this -> resetMotorEncoders();

    float targetPosition = dist; // dist * 300/2pir

    float targetAngle = this -> getIMURotation();

    float kIMU = 4;
    float angleError = 0.0;
    float imuCorrection = 0.0;
    float chassisPower = 0.0;

    while (!(chassisPID.isSettled())) {
        float chassisError = targetPosition - ticksToInches(this -> getAvgEncoderValue());

        float chassisOutput = chassisPID.compute(chassisError);

        angleError = targetAngle - this -> getIMURotation();

        imuCorrection = kIMU * angleError;

        chassisPID.checkIfSettled(targetPosition - ticksToInches((Nova::backLeft.get_position() + Nova::backRight.get_position()) / 2));

        chassisPower = chassisOutput > maxSpeed ? maxSpeed : (chassisOutput < -maxSpeed ? -maxSpeed : chassisOutput);

        //ctr.print(0, 0, "%0.2f", this -> chassis.getIMURotation());

        if (dist > 0.0) {
            Nova::leftDrive.move((chassisPower + imuCorrection));
            Nova::rightDrive.move((chassisPower - imuCorrection));
        } else {
            Nova::leftDrive.move((chassisPower + imuCorrection));
            Nova::rightDrive.move((chassisPower - imuCorrection));
        }

        pros::delay(10);
    }

    drive.brake();

    chassisPID.reset();

    // Nova::ctr.print(0, 0, "%0.2f", chassis.getIMURotation());
}


    // 5.85, 0, 40, 0, 5, 200 - 90 degrees for 90 degrees
    // 5.85, 0, 40, 0, 5, 200 - 45 degrees for 45 degrees
    // 5.5, 0, 40, 0, 5, 200 - 180 degrees for 180 degrees

void Nova::Chassis::rotate(float angle) {
    Nova::PID turnPID = Nova::PID(0,0,0,0,0,0);
    if (fabsf(angle) >= 180) {
        turnPID = Nova::PID(1.4, 0, 7, 0, 8, 150);
    } else if (fabsf(angle) >= 90 && fabs(angle) < 180) {
        turnPID = Nova::PID(1.45, 0, 7, 0, 8, 150);
    } else if (fabs(angle) >= 45 && fabsf(angle) < 90) {
        turnPID = Nova::PID(1.5, 0, 7, 0, 5, 150);
    } else {
        turnPID = Nova::PID(1.5, 0, 2, 0, 5, 150);
    }

    float targetPosition = this -> getIMURotation() + angle;

    while (!(turnPID.isSettled())) {
        float error = targetPosition - this -> getIMURotation();

        float power = turnPID.compute(error);

        turnPID.checkIfSettled(error);

        float chassisPower = power > 120 ? 120 : (power < -120 ? -120 : power);

        Nova::leftDrive.move(chassisPower);
        Nova::rightDrive.move(-chassisPower);

        pros::delay(10);
    }

    drive.brake();

    turnPID.reset();
}


/*
void Nova::Chassis::driveAngle(double targetDistance, double targetHeading, double timeout, bool resetSensors = true, double rushErrorThreshold = -1, double slewRate = -1)
{
    int startTime = pros::millis();

    Nova::PID chassisPID = Nova::PID(
        5, // kp
        0,  // ki
        0, // kd increasing this will make more smooth
        0, // tolerance
        0,  // integralshreshold
        0 // max integral
    );

     Nova::PID turnPID = Nova::PID(
        2.5,  // kp
        0,  // ki
        0, // kd
        0, // tolerance
        0,  // integralshreshold
        0 // max integral
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
*/