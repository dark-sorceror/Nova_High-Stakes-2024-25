/**
 * \file globals.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#include "main.h"

namespace Nova
{
    const std::string TEAM_NAME = "Nova";
    const std::string TEAM_NUMBER = "3388N";
    const char *VERSION = "V1";

    pros::Controller ctr(pros::E_CONTROLLER_MASTER);

    pros::Motor frontLeft(-1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleLeft(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backLeft(12, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor frontRight(10, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor middleRight(19, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);
    pros::Motor backRight(-20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::counts);

    pros::Motor conveyor(11);
    pros::Motor intake(14);

    //pros::Optical optical(16);
 
    pros::MotorGroup leftDrive(
        {frontLeft.get_port(),
         middleLeft.get_port(),
         backLeft.get_port()});
    pros::MotorGroup rightDrive(
        {frontRight.get_port(),
         middleRight.get_port(),
         backRight.get_port()});
    pros::MotorGroup drive(
        {frontLeft.get_port(),
         middleLeft.get_port(),
         backLeft.get_port(),
         frontRight.get_port(),
         middleRight.get_port(),
         backRight.get_port()});

    pros::Imu imu1(3);
    pros::Imu imu2(9);

    pros::adi::Pneumatics clamp('H', LOW);

    pros::Rotation horizontalEncoder(2);
}