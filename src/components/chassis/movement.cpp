/**
 * \file movement.cpp
 *
 * \brief Contains Chassis movement in autonomous
 * 
 * \date Updated - 12/25/2024
 */

#include "globals.h"
#include "utils.h"
#include "pid.h"

#include "components/chassis/chassis.h"

float distanceBetweenPoints(const Point &a, const Point &b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float calculateCurvature(const Point &prev, const Point &curr, const Point &next) {
    float angle1 = atan2(curr.y - prev.y, curr.x - prev.x);
    float angle2 = atan2(next.y - curr.y, next.x - curr.x);

    return (angle2 - angle1);
}

/**
 * @brief Translate the Robot in x or y directions
 *
 * @param dist //inches
 */
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
        float chassisError = targetPosition - 
        (((Nova::backLeft.get_position() + Nova::backRight.get_position())/2) / 44.07367655);

        float chassisOutput = chassisPID.compute(chassisError, true);

        float currentOrientation = this -> getIMURotation();

        angleError = fabs(targetAngle - currentOrientation) * -sgn(currentOrientation);

        imuCorrection = kIMU * angleError;

        chassisPID.checkIfSettled(targetPosition - 
        (((Nova::backLeft.get_position() + Nova::backRight.get_position()) / 2) / 44.07367655));

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

void Nova::Chassis::followPath(const std::vector<Point> &waypoints) {
    Nova::PID chassisPID = Nova::PID(
        7,  // kp
        4,  // ki
        50, // kd
        0, // max cumulative error inches
        8,  // settle error inchjes
        100 // settle time MILLIS
    );

    this -> resetMotorEncoders();
    float targetPosition = 0.0;
    float currentPosition = 0.0;

    for (size_t i = 0; i < waypoints.size() - 1; ++i) {
        Point startPoint = waypoints[i];
        Point endPoint = waypoints[i + 1];

        float segmentDistance = distanceBetweenPoints(startPoint, endPoint);

        float curvature = 0.0f;

        if (i > 0 && i < waypoints.size() - 1) {
            curvature = calculateCurvature(waypoints[i - 1], startPoint, endPoint);
        }

        targetPosition += segmentDistance;

        currentPosition = Nova::backLeft.get_position() / 46.28245103;

        while (fabs(targetPosition - currentPosition) > 30) {
            float chassisError = targetPosition - currentPosition;

            float chassisOutput = chassisPID.compute(chassisError, false);

            float maxPower = 120;
            float distanceToTarget = fabs(targetPosition - currentPosition);
            float powerScale = fmax(0.1, fmin(1.0, distanceToTarget / segmentDistance));

            float leftSpeed = chassisOutput * powerScale;
            float rightSpeed = chassisOutput * powerScale;

            if (curvature > 0) {
                leftSpeed -= curvature * 50;
                rightSpeed += curvature * 50;
            } else if (curvature < 0) {
                leftSpeed += (-curvature) * 50;
                rightSpeed -= (-curvature) * 50;
            }

            leftSpeed = fmin(fmax(leftSpeed, -120), 120);
            rightSpeed = fmin(fmax(rightSpeed, -120), 120);

            leftDrive.move(leftSpeed);
            rightDrive.move(rightSpeed);

            currentPosition = backLeft.get_position() / 46.28245103;

            pros::delay(10);
        }

        drive.brake();

        chassisPID.reset();
    }
}