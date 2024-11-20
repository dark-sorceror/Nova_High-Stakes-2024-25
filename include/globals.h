/**
 * \file globals.h
 *
 * Updated - 11/17/2024
 * Last Successful Test - 11/17/2024
 */

#ifndef __GLOBALS
#define __GLOBALS

#include "api.h"

namespace Nova {
    extern const std::string TEAM_NAME;
    extern const std::string TEAM_NUMBER;
    extern const char * VERSION;

    extern pros::v5::Controller ctr;

    extern pros::v5::Motor frontLeft;
    extern pros::v5::Motor middleLeft;
    extern pros::v5::Motor backLeft;
    extern pros::v5::Motor frontRight;
    extern pros::v5::Motor middleRight;
    extern pros::v5::Motor backRight;

    extern pros::v5::MotorGroup leftDrive;
    extern pros::v5::MotorGroup rightDrive;
    extern pros::v5::MotorGroup drive;
}

#endif