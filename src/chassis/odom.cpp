#include <math.h>
#include "pros/rtos.hpp"
#include "main.h"

Nova::Pose odomPose(0, 0, 0);
Nova::Pose odomSpeed(0, 0, 0);
Nova::Pose odomLocalSpeed(0, 0, 0);

float prevVertical = 0;
float prevVertical1 = 0;
float prevHorizontal = 0;
float prevHorizontal1 = 0;
float prevImu = 0;

float degToRad(float value) {
    return value * M_PI / 180;
}

float radToDeg(float value) {
    return value * 180 / M_PI;
}

Nova::Pose Nova::getPose(bool radians) {
    if (radians) return odomPose;
    else return Nova::Pose(odomPose.x, odomPose.y, radToDeg(odomPose.theta));
}

void Nova::setPose(Nova::Pose pose, bool radians) {
    if (radians) odomPose = pose;
    else odomPose = Nova::Pose(pose.x, pose.y, degToRad(pose.theta));
}

float getVerticalDistanceTraveled() {
    return ((Nova::backLeft.get_position() + Nova::backRight.get_position() + \
            Nova::middleLeft.get_position() + Nova::middleRight.get_position() + \
            Nova::frontLeft.get_position() + Nova::frontRight.get_position()) / 6) * 3.25 * M_PI * (450 / 600);
}

float getHorizontalDistanceTraveled() {
    return (float(Nova::horizontalEncoder.get_position()) * 2 * M_PI / 36000) / 1;
}

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

    pros::lcd::print(1, "x: %0.2f y: %0.2f theta: %0.2f", odomPose.x, odomPose.y, odomPose.theta);
}