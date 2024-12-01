/**
 * \file main.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#include "main.h"

Nova::Brain brain = Nova::Brain();
Nova::Drive drive = Nova::Drive();
Nova::Intake intake = Nova::Intake();
Nova::Clamp clamp = Nova::Clamp();
Nova::Auton auton = Nova::Auton(drive, intake);

void initialize()
{
    brain.initialize();

    //change later

    Nova::frontLeft.tare_position();
    Nova::middleLeft.tare_position();
    Nova::backLeft.tare_position();
    Nova::frontRight.tare_position();
    Nova::middleRight.tare_position();
    Nova::backRight.tare_position();

    Nova::imu1.reset();
    Nova::imu2.reset();
}

void disabled() {}

void competition_initialize()
{
    brain.initialize();

    //change later

    Nova::frontLeft.tare_position();
    Nova::middleLeft.tare_position();
    Nova::backLeft.tare_position();
    Nova::frontRight.tare_position();
    Nova::middleRight.tare_position();
    Nova::backRight.tare_position();

    Nova::imu1.reset();
    Nova::imu2.reset();

    autonomous();
}

void autonomous()
{
    auton.test();
    //Nova::moveToPos(10.0, 10.0, M_PI / 2.0); // 10 cm, 10 cm, 90 degrees
}

void opcontrol()
{
    while (true)
    {
        intake.run();
        clamp.run();
        drive.run();
        pros::delay(10);
    }
}