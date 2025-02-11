/**
 * \file globals.h
 *
 * \brief Contains definitions for globals.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "api.h"

namespace Nova {
    extern const std::string TEAM_NAME;
    extern const std::string TEAM_NUMBER;
    extern const char * VERSION;

    // Controller
    extern pros::v5::Controller ctr;

    // Chassis
    //extern const float wheelDiameter;
    //extern const int driveRPM;

    extern pros::v5::Motor frontLeft;
    extern pros::v5::Motor middleLeft;
    extern pros::v5::Motor backLeft;
    extern pros::v5::Motor frontRight;
    extern pros::v5::Motor middleRight;
    extern pros::v5::Motor backRight;

    extern pros::v5::MotorGroup leftDrive;
    extern pros::v5::MotorGroup rightDrive;
    extern pros::v5::MotorGroup drive;

    // Components
    extern pros::v5::Motor intake;

    extern pros::adi::Pneumatics clamp;
    extern pros::adi::Pneumatics doinker;
    extern pros::adi::Pneumatics raiseIntake;
    extern pros::adi::Pneumatics goalRush;
    extern pros::adi::Pneumatics colorSort;

    // Auton Dependent
    extern pros::v5::Imu imu1;
    extern pros::v5::Imu imu2;

    extern pros::v5::Optical optical;

    extern pros::v5::Motor lb;
    extern pros::v5::Rotation lbCheck;

    extern pros::v5::Distance clampCheck;

    extern pros::v5::Rotation horizontalEncoder;
}; // namespace Nova

#endif // _GLOBALS_H_