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

    //const float wheelDiameter = 3.25;
    //const int driveRPM = 450;

    pros::Motor frontLeft(-18, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft(-20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backLeft(19, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor frontRight(6, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleRight(7, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backRight(-8, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

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

    pros::Motor intake(5);

    pros::adi::Pneumatics clamp('H', true, true);
    pros::adi::Pneumatics raiseIntake('A', true, false);
    pros::adi::Pneumatics doinker('B', false, false);

    pros::Optical optical(4);

    pros::Imu imu1(9);
    pros::Imu imu2(10);

    pros::Motor lb1(2);
    pros::Motor lb2(3);
    pros::Rotation lbCheck(1);

    pros::Rotation horizontalEncoder(2);
} // namespace Nova