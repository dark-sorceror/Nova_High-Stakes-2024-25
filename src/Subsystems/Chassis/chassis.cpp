/**
 * \file Chassis.cpp
 *
 * \brief Contains Chassis logic in user control and initialization
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#include "main.h"

//WIP -> make more modularized and temperature safety
/**
 * @brief Initialize Chassis
 * 
 */
void Nova::Chassis::initialize() {
    this -> resetMotorEncoders();
    horizontalEncoder.reset();
    this -> setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

/**
 * @brief Logarthmic Chassis
 * 
 * @param input - The input from the controller joysticks for speed of motor
 * @return double 
 */
double Nova::Chassis::smooth(double input) {
    const int CURVECONSTANT = 10;

    return (std::pow(2.718, -(CURVECONSTANT / 10)) + std::pow(2.718, (std::abs(input) - 127) / 10) * (1 - std::pow(2.718, -(CURVECONSTANT / 10)))) * input;
}

/**
 * @brief Calibrate Chassis
 * 
 */
void Nova::Chassis::calibrate() {
    if (imu1.is_installed() && imu2.is_installed()) {
        int attempt = 1;
        bool calibrated = false;

        while (attempt <= 5) {
            imu1.reset();
            imu2.reset();

            do pros::delay(10);
            while (
                (imu1.get_status() != pros::ImuStatus::error && imu2.get_status() != pros::ImuStatus::error) 
                &&
                (imu1.is_calibrating() && imu2.is_calibrating())
            );

            if (
                (!isnanf(imu1.get_heading()) && !isnanf(imu2.get_heading())) 
                && 
                (!std::isinf(imu1.get_heading()) && !std::isinf(imu2.get_heading()))
            ) {
                calibrated = true;
                break;
            }

            pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, "---");
            // log
            attempt++;
        }

        if (attempt > 5) {
            // log
        }
    }
    
    pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
}

/**
 * @brief Run the Chassis
 * 
 */
void Nova::Chassis::run() {
    int power = smooth(Nova::ctr.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int turn = smooth(Nova::ctr.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

    leftDrive.move_voltage((power + turn) * (12000.0 / 127));
    rightDrive.move_voltage((power - turn) * (12000.0 / 127));
}