/**
 * \file globals.cpp
 * 
 * Updated - 11/17/2024
 * Last Successful Test - 11/17/2024
 */

#include "api.h"
#include "globals.h"

namespace Nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";
    const char * VERSION = "v1.0.0";

    pros::Controller ctr (pros::E_CONTROLLER_MASTER);

    pros::Motor frontLeft (-2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft (-1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backLeft (-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor frontRight (9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleRight (8, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backRight (20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::MotorGroup leftDrive ({ frontLeft.get_port(), middleLeft.get_port(), backLeft.get_port() });
    pros::MotorGroup rightDrive ({ frontRight.get_port(), middleRight.get_port(), backRight.get_port() });
    pros::MotorGroup drive ({ frontLeft.get_port(), middleLeft.get_port(), backLeft.get_port(), frontRight.get_port(), middleRight.get_port(), backRight.get_port() });
}