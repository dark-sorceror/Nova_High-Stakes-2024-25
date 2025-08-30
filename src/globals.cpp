/**
 * \file globals.cpp
 *
 * \brief Contains variables for ports
 * 
 * \date Updated - 2/10/2025
 */

#include "api.h"

namespace Nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";
    const char *VERSION = "V2";

    pros::Controller ctr(pros::E_CONTROLLER_MASTER);

    //const float wheelDiameter = 3.25;
    //const int driveRPM = 450;

    pros::Motor frontLeft(-9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft(-16, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backLeft(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor frontRight(8, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleRight(17, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backRight(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::MotorGroup leftDrive(
        {
            frontLeft.get_port(),
            middleLeft.get_port(),
            backLeft.get_port()
        }
    );

    pros::MotorGroup rightDrive(
        {
            frontRight.get_port(),
            middleRight.get_port(),
            backRight.get_port()
        }
    );

    pros::MotorGroup drive(
        {
            frontLeft.get_port(),
            middleLeft.get_port(),
            backLeft.get_port(),
            frontRight.get_port(),
            middleRight.get_port(),
            backRight.get_port()
        }
    );

    pros::Motor intake(12);
    //pros::adi::Pneumatics colorSort('B', false, false);
    pros::Optical colorCheck(4);
    pros::adi::Pneumatics intakePiston('C', false, false);

    pros::adi::Pneumatics clamp('A', false, false);
    pros::Distance clampCheck(1);

    pros::adi::Pneumatics doinker('B', false, false);

    pros::Motor lb(13);
    pros::Rotation lbCheck(3);

    // Auton dependent
    pros::Imu imu1(6);
    pros::Imu imu2(7);

    pros::Rotation horizontalEncoder(20);
} // namespace Nova