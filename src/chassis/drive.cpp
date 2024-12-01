/**
 * \file drive.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#include "main.h"

void Nova::Drive::initialize() {
    Nova::frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    Nova::middleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    Nova::backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    Nova::frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    Nova::middleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    Nova::backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Nova::Drive::resetMotorEncoders() {
    Nova::frontLeft.tare_position();
    Nova::middleLeft.tare_position();
    Nova::backLeft.tare_position();
    Nova::frontRight.tare_position();
    Nova::middleRight.tare_position();
    Nova::backRight.tare_position();
}

void Nova::Drive::resetIMU() {
    Nova::imu1.reset();
    Nova::imu2.reset();
}

float Nova::Drive::getAvgEncoderValue() {
    return (Nova::frontLeft.get_position() + Nova::middleLeft.get_position() + Nova::backLeft.get_position() + Nova::frontRight.get_position() + Nova::middleRight.get_position() + Nova::backRight.get_position())/6;
}

float Nova::Drive::getAvgVelocity() {
    return (Nova::frontLeft.get_actual_velocity() + Nova::middleLeft.get_actual_velocity() + Nova::backLeft.get_actual_velocity() + Nova::frontRight.get_actual_velocity() + Nova::middleRight.get_actual_velocity() + Nova::backRight.get_actual_velocity())/6;
}

double Nova::Drive::getIMURotation() {
    return (Nova::imu1.get_rotation() + Nova::imu2.get_rotation()) / 2;
}

void Nova::Drive::run() {
    int power = smooth(Nova::ctr.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int turn = smooth(Nova::ctr.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

    leftDrive.move_voltage((power + turn) * (12000.0 / 127));
    rightDrive.move_voltage((power - turn) * (12000.0 / 127));
}

double Nova::Drive::smooth(double input) {
    const int CURVECONSTANT = 0.25;

    return  (std::pow(2.718, -(CURVECONSTANT / 10)) + std::pow(2.718, (std::abs(input) - 127) / 10) * (1 - std::pow(2.718, -(CURVECONSTANT / 10)))) * input;
}