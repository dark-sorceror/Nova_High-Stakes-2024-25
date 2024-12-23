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
        1,  // kp
        0,  // ki
        12, // kd
        10, // max cumulative error inches
        5,  // settle error inchjes
        100 // settle time MILLIS
    );

    this -> chassis.resetMotorEncoders();

    float targetPosition = dist; // dist * 300/2pir

    float targetAngle = this -> chassis.getIMURotation();

    while (!(chassisPID.isSettled())) {
        float chassisError = targetPosition - 
        (((Nova::backLeft.get_position() + Nova::backRight.get_position())/2)/44.07367655);

        float chassisOutput = chassisPID.compute(chassisError);

        float angleError = this -> chassis.getIMURotation() - targetAngle;

        float kIMU = 0.5;
        float imuCorrection = kIMU * angleError;

        chassisPID.checkIfSettled(targetPosition - 
        (((Nova::backLeft.get_position() + Nova::backRight.get_position()) / 2) / 44.07367655));

        float chassisPower = chassisOutput > 120 ? 120 : (chassisOutput < -120 ? -120 : chassisOutput);

        Nova::leftDrive.move(chassisPower);
        Nova::rightDrive.move(chassisPower);

        pros::delay(10);
    }

    chassisPID.reset();

    // Nova::ctr.print(0, 0, "%0.2f", chassis.getIMURotation());
}

void Nova::Auton::rotate(float angle) {
    Nova::PID turnPID = Nova::PID(
        1,   // kp
        0,   // ki
        0,   // kd
        110, // max cumulative error degrees
        10,  // settle error degrees
        100  // settle time MILLIS
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

float distanceBetweenPoints(const Point &a, const Point &b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float calculateCurvature(const Point &prev, const Point &curr, const Point &next) {
    float angle1 = atan2(curr.y - prev.y, curr.x - prev.x);
    float angle2 = atan2(next.y - curr.y, next.x - curr.x);

    return (angle2 - angle1);
}

void Nova::Auton::followPath(const std::vector<Point> &waypoints) {
    Nova::PID chassisPID = Nova::PID(
        1,  // kp
        0,  // ki
        12, // kd
        10, // max cumulative error inches
        5,  // settle error inchjes
        100 // settle time MILLIS
    );

    this -> chassis.resetMotorEncoders();
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

        while (fabs(targetPosition - currentPosition) > 1) {
            float chassisError = targetPosition - currentPosition;

            float chassisOutput = chassisPID.compute(chassisError);

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

            Nova::leftDrive.move(leftSpeed);
            Nova::rightDrive.move(rightSpeed);

            currentPosition = Nova::backLeft.get_position() / 46.28245103;

            pros::delay(10);
        }

        Nova::drive.brake();

        chassisPID.reset();
    }
}

void Nova::Auton::blue1Elims() {
    std::vector<Point> waypoints = {
        {0.0, 0.0},   // Start point
        {10.0, 0.0},  // Waypoint 1
        {15.0, 5.0},  // Waypoint 2 (curved segment)
        {20.0, 0.0},  // Waypoint 3
        {30.0, -5.0}, // Waypoint 4 (curved segment)
        {40.0, 0.0}   // End point
    };

    this -> followPath(waypoints);
}