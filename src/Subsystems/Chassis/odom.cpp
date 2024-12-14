/**
 * \file odom.cpp
 *
 * \brief Contains odom (tracking algorithm) logic
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#include <math.h>

#include "main.h"

Nova::Pose odomPose(0, 0, 0);
Nova::Pose odomSpeed(0, 0, 0);
Nova::Pose odomLocalSpeed(0, 0, 0);

float prevVertical = 0;
float prevVertical1 = 0;
float prevHorizontal = 0;
float prevHorizontal1 = 0;
float prevImu = 0;

/**
 * @brief Convert from degree to radians
 *
 * @param value
 * @return float
 */
extern float degToRad(float value) {
    return value * M_PI / 180;
}

/**
 * @brief Convert from radians to degrees
 *
 * @param value
 * @return float
 */
extern float radToDeg(float value) {
    return value * 180 / M_PI;
}

/**
 * @brief Get position of Pose object
 * 
 * @param radians 
 * @return Nova::Pose 
 */
Nova::Pose Nova::getPose(bool radians) {
    if (radians) return odomPose;
    else return Nova::Pose(odomPose.x, odomPose.y, radToDeg(odomPose.theta));
}

/**
 * @brief Set position of Pose object
 * 
 * @param pose 
 * @param radians 
 */
void Nova::setPose(Nova::Pose pose, bool radians) {
    if (radians) odomPose = pose;
    else odomPose = Nova::Pose(pose.x, pose.y, degToRad(pose.theta));
}

/**
 * @brief Get the Vertical Distance Traveled object
 * 
 * @return float 
 */
float getVerticalDistanceTraveled() {
    return ((Nova::backLeft.get_position() + Nova::backRight.get_position() + \
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
 * @brief Tracking Algorithm Loop
 * 
 */
void Nova::update() {
    float imuRaw = 0;

    imuRaw = degToRad((Nova::imu1.get_rotation() + Nova::imu2.get_rotation()) / 2);

    float deltaImu = imuRaw - prevImu;

    prevImu = imuRaw;
 
    float heading = odomPose.theta;
    
    heading += deltaImu;

    float deltaHeading = heading - odomPose.theta;
    float avgHeading = odomPose.theta + deltaHeading / 2;

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

    Nova::Pose prevPose = odomPose;

    odomPose.x += localY * sin(avgHeading);
    odomPose.y += localY * cos(avgHeading);
    odomPose.x += localX * -cos(avgHeading);
    odomPose.y += localX * sin(avgHeading);
    odomPose.theta = heading;

    // testing
    pros::lcd::print(1, "x: %0.2f y: %0.2f theta: %0.2f", odomPose.x, odomPose.y, odomPose.theta);
}