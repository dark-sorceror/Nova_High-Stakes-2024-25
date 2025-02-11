/**
 * \file globals.cpp
 *
 * \brief Contains variables for ports
 * 
 * \date Updated - 1/20/2025
 */

#include "api.h"

namespace Nova {
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";
    const char *VERSION = "V2";

    pros::Controller ctr(pros::E_CONTROLLER_MASTER);

    //const float wheelDiameter = 3.25;
    //const int driveRPM = 450;

    pros::Motor frontLeft(-1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft(-2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backLeft(3, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor frontRight(11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleRight(12, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backRight(-13, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

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

    pros::Motor intake(-8);

    pros::adi::Pneumatics clamp('A', false, false);
    pros::adi::Pneumatics colorSort('B', false, false);
    pros::adi::Pneumatics raiseIntake('C', false, false);
    pros::adi::Pneumatics doinker('D', false, false);

    pros::Optical optical(4);

    pros::Imu imu1(9);
    pros::Imu imu2(10);

    pros::Motor lb(16);
    pros::Rotation lbCheck(5);

    pros::Distance clampCheck(15);

    pros::Rotation horizontalEncoder(20);
} // namespace Nova