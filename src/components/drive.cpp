/**
 * \file drive.cpp
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */ 

#include "globals.h"
#include "main.h"
#include "pros/motors.h"

void nova::Drive::initialize() {
    nova::frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    nova::frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    nova::backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void nova::Drive::resetMotorEncoders() {
    nova::frontLeft.tare_position();
    nova::middleLeft.tare_position();
    nova::backLeft.tare_position();

    nova::frontRight.tare_position();
    nova::middleRight.tare_position();
    nova::backRight.tare_position();
}

float nova::Drive::getAvgEncoderValue() {
    return (nova::frontLeft.get_position() + nova::middleLeft.get_position() + 
            nova::backLeft.get_position() + nova::frontRight.get_position() + 
            nova::middleRight.get_position() + nova::backRight.get_position()) / 6;
}

float nova::Drive::getAvgVelocity() {
    return (nova::frontLeft.get_actual_velocity() + nova::middleLeft.get_actual_velocity() + 
            nova::backLeft.get_actual_velocity() + nova::frontRight.get_actual_velocity() + 
            nova::middleRight.get_actual_velocity() + nova::backRight.get_actual_velocity()) / 6;
}

void nova::Drive::run() {
    int x = ctr.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	int y = ctr.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

    x = 0 ? (abs(x) <= this -> DEADBAND) : x;
    y = 0 ? (abs(y) <= this -> DEADBAND) : y;

    nova::frontLeft.move(y + x);
    nova::middleLeft.move(y + x);
    nova::backLeft.move(y + x);

    nova::frontRight.move(y - x);
    nova::middleRight.move(y - x);
    nova::backRight.move(y - x);

    //master.print(0, 0, "%f", this->getIMURotation());
    //master.print(0, 0, "%f", this->getAvgEncoderValue());
}