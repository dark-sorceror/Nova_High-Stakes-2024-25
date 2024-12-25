/**
 * \file globals.cpp
 *
 * \brief Contains variables for ports
 * 
 * \date Updated - 12/25/2024
 */

#include "api.h"

namespace Nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";
    const char *VERSION = "V2";

    pros::Controller ctr(pros::E_CONTROLLER_MASTER);

    const float wheelDiameter = 3.25;
    const int driveRPM = 450;

    pros::Motor frontLeft(-8, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft(-9, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backLeft(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor frontRight(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleRight(2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backRight(-3, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

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

    pros::Motor intake(6);

    pros::adi::Pneumatics clamp('A', true, true);
    pros::adi::Pneumatics doinker('B', true, false);

    pros::Optical optical(5);

    pros::Imu imu1(19);
    pros::Imu imu2(20);

    pros::Rotation horizontalEncoder(2);
} // namespace Nova