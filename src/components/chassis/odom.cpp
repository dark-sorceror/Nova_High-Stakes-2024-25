/**
 * \file odom.cpp
 *
 * \brief Contains odometry (tracking algorithm) logic
 * 
 * \date Updated - 1/6/2025
 */

#include "components/chassis.h"

Nova::Pose currentPosition(0, 0, 0);

float prevVertical = 0;
float prevVertical1 = 0;
float prevHorizontal = 0;
float prevHorizontal1 = 0;
float prevImu = 0;

/**
 * @brief Get the Vertical Distance Traveled object
 * 
 * @return float 
 */
float getVerticalDistanceTraveled() {
    return (
        (Nova::backLeft.get_position() + Nova::backRight.get_position() + \
            Nova::middleLeft.get_position() + Nova::middleRight.get_position() + \
            Nova::frontLeft.get_position() + Nova::frontRight.get_position()) / 6) * 3.25 * M_PI * (450 / 600);
}

/**
 * @brief Get the Horizontal Distance Traveled object
 * 
 * @return float 
 */
float getHorizontalDistanceTraveled() {
    return (float(Nova::horizontalEncoder.get_position()) * 2 * M_PI / 36000) / 1;
}

/**
 * @brief Convert from degree to radians
 *
 * @param value
 * @return float
 */
float degToRad(float degrees) {
    return degrees * M_PI / 180;
}

/**
 * @brief Convert from radians to degrees
 *
 * @param value
 * @return float
 */
float radToDeg(float radians) {
    return radians * 180 / M_PI;
}

/**
 * @brief Get position of Pose object
 * 
 * @param radians 
 * @return Nova::Pose 
 */
Nova::Pose Nova::Chassis::getCurrentPosition(bool radians) {
    if (radians) return currentPosition;
    else return Nova::Pose(currentPosition.x, currentPosition.y, radToDeg(currentPosition.theta));
}

/**
 * @brief Set position of Pose object
 * 
 * @param pose 
 * @param radians 
 */
void Nova::Chassis::setPosition(Nova::Pose pose, bool radians) {
    if (radians) currentPosition = pose;
    else currentPosition = Nova::Pose(pose.x, pose.y, degToRad(pose.theta));
}

/**
 * @brief Tracking Algorithm Loop
 * 
 */
void Nova::Chassis::updatePosition() {
    float imuRaw = 0;

    imuRaw = degToRad((Nova::imu1.get_rotation() + Nova::imu2.get_rotation()) / 2);

    float deltaImu = imuRaw - prevImu;

    prevImu = imuRaw;
 
    float heading = currentPosition.theta;
    
    heading += deltaImu;

    float deltaHeading = heading - currentPosition.theta;
    float avgHeading = currentPosition.theta + deltaHeading / 2;

    float rawVertical = 0;
    float rawHorizontal = 0;
    rawVertical = getVerticalDistanceTraveled();
    rawHorizontal = getHorizontalDistanceTraveled();

    float horizontalOffset = 6.2;
    float verticalOffset = 6.2;

    float deltaX = 0;
    float deltaY = 0;
    deltaY = rawVertical - prevVertical;
    deltaX = rawHorizontal - prevHorizontal;
    prevVertical = rawVertical;
    prevHorizontal = rawHorizontal;

    float localX = 0;
    float localY = 0;
    if (deltaHeading == 0) {
        localX = deltaX;
        localY = deltaY;
    } else {
        localX = 2 * sin(deltaHeading / 2) * (deltaX / deltaHeading + horizontalOffset);
        localY = 2 * sin(deltaHeading / 2) * (deltaY / deltaHeading + verticalOffset);
    }

    Nova::Pose prevPose = currentPosition;

    currentPosition.x += localY * sin(avgHeading);
    currentPosition.y += localY * cos(avgHeading);
    currentPosition.x += localX * -cos(avgHeading);
    currentPosition.y += localX * sin(avgHeading);
    currentPosition.theta = heading;

    // testing
    pros::lcd::print(1, "x: %0.2f y: %0.2f theta: %0.2f", currentPosition.x, currentPosition.y, currentPosition.theta);
}