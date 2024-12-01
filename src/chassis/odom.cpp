/**
 * \file odom.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 
 */ 

#include "main.h"

double x = 0.0;
double y = 0.0;
double theta = 0.0; // radians

const double wheel_circumference = 8.255;  // cm
const double encoder_ticks_per_rev = 300.0;

void Nova::updateOdometry() {
    double avg_vertical_position = (frontLeft.get_position() + middleLeft.get_position() + backLeft.get_position()) / 3.0;
    
    double distance_traveled = (avg_vertical_position / encoder_ticks_per_rev) * wheel_circumference;

    double rotation = ((imu1.get_rotation() + imu2.get_rotation()) / 2) * (M_PI / 180.0);

    x += distance_traveled * cos(theta);
    y += distance_traveled * sin(theta);
    theta = rotation; 
}

void Nova::moveToPos(double target_x, double target_y, double target_theta) {
    while (true) {
        updateOdometry();

        double error_x = target_x - x;
        double error_y = target_y - y;
        double error_theta = target_theta - theta;

        if (fabs(error_x) < 1.0 && fabs(error_y) < 1.0 && fabs(error_theta) < 0.1) {
            break;
        }

        double speed_x = error_x * 0.1;
        double speed_y = error_y * 0.1;
        double speed_theta = error_theta * 0.1;

        leftDrive.move_velocity(speed_x + speed_theta);
        rightDrive.move_velocity(speed_x - speed_theta);

        pros::delay(20);
    }
}