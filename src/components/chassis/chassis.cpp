/**
 * \file chassis.cpp
 *
 * \brief Contains Chassis logic in user control and initialization
 * 
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#include "globals.h"

#include "components/chassis/chassis.h"

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
 * @brief Get average encoder value of the Chassis
 *
 * @return float
 */
float Nova::Chassis::getAvgEncoderValue() {
    return (
            Nova::frontLeft.get_position() +
            Nova::middleLeft.get_position() +
            Nova::backLeft.get_position() +
            Nova::frontRight.get_position() +
            Nova::middleRight.get_position() +
            Nova::backRight.get_position()) /
        6;
}

/**
 * @brief Get average velocity value of the Chassis
 *
 * @return float
 */
float Nova::Chassis::getAvgVelocity() {
    return (
            Nova::frontLeft.get_actual_velocity() +
            Nova::middleLeft.get_actual_velocity() +
            Nova::backLeft.get_actual_velocity() +
            Nova::frontRight.get_actual_velocity() +
            Nova::middleRight.get_actual_velocity() +
            Nova::backRight.get_actual_velocity()) /
        6;
}

/**
 * @brief Get average IMU rotation; orientiation of the Chassis
 *
 * @return double
 */
float Nova::Chassis::getIMURotation() {
    return (Nova::imu1.get_rotation() + Nova::imu2.get_rotation()) / 2;
}

/**
 * @brief Reset motor encoders of chassis
 * 
 */
void Nova::Chassis::resetMotorEncoders() {
    drive.tare_position_all();
}

/**
 * @brief Change brake mode of Chassis
 *
 * @param brakeMode
 */
void Nova::Chassis::setBrakeMode(pros::motor_brake_mode_e_t brakeMode) {
    drive.set_brake_mode_all(brakeMode);
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
 * @brief Logarthmic Chassis
 * 
 * @param input - The input from the controller joysticks for speed of motor
 * @return double 
 */
double Nova::Chassis::smooth(double input) {
    const int CURVECONSTANT = 5;

    return (std::pow(2.718, -(CURVECONSTANT / 10)) + std::pow(2.718, (std::abs(input) - 127) / 10) * (1 - std::pow(2.718, -(CURVECONSTANT / 10)))) * input;
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