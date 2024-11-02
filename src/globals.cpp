/**
 * \file globals.cpp
 * 
 * Updated - 10/24/2024
 * Last Successful Test - 
 */

#include "api.h"
#include "globals.h"

namespace nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";

    pros::Motor frontLeft (1, pros::v5::MotorGears::green, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft (1, pros::v5::MotorGears::green, pros::v5::MotorUnits::counts);
    pros::Motor backLeft (1, pros::v5::MotorGears::green, pros::v5::MotorUnits::counts);

    pros::Motor frontRight (1, pros::v5::MotorGears::green, pros::v5::MotorUnits::counts);
    pros::Motor middleRight (1, pros::v5::MotorGears::green, pros::v5::MotorUnits::counts);
    pros::Motor backRight (1, pros::v5::MotorGears::green, pros::v5::MotorUnits::counts);

    pros::MotorGroup leftDrive ({ frontLeft.get_port(), middleLeft.get_port(), backLeft.get_port() });
    pros::MotorGroup rightDrive ({ frontRight.get_port(), middleRight.get_port(), backRight.get_port() });
    pros::MotorGroup drive ({ frontLeft.get_port(), middleLeft.get_port(), backLeft.get_port(), frontRight.get_port(), middleRight.get_port(), backRight.get_port() });

    pros::Motor intake (1, pros::v5::MotorGear::blue, pros::v5::MotorUnits::counts);

    pros::adi::Pneumatics clamp ('A', false, true);

    pros::Rotation odometryWheel (1);

    pros::Imu imu1 (1);
    pros::Imu imu2 (1);
}