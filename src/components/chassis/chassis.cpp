/**
 * \file chassis.cpp
 *
 * \brief Contains Chassis logic in user control and initialization
 * 
 * \date Updated - 12/25/2024
 */

#include "globals.h"
#include "utils.h"

#include "components/chassis/chassis.h"

/**
 * @brief Initialize Chassis
 * 
 */
void Nova::Chassis::initialize() {
    this -> resetMotorEncoders();
    //horizontalEncoder.reset();
    this -> resetIMUs();

    this -> setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

    imu1.set_data_rate(5);
    imu2.set_data_rate(5);
}

/**
 * @brief Get average encoder value of the Chassis
 *
 * @return float
 */
float Nova::Chassis::getAvgEncoderValue() {
    return average(Nova::drive.get_position_all());
}

/**
 * @brief Get average velocity value of the Chassis
 *
 * @return float
 */
float Nova::Chassis::getAvgVelocity() {
    return average(Nova::drive.get_actual_velocity_all());
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

void Nova::Chassis::resetIMUs() {
    imu1.reset();
    imu2.reset();
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
    int power = smooth(ctr.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    int turn = smooth(ctr.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

    leftDrive.move_voltage((power + turn) * (12000.0 / 127));
    rightDrive.move_voltage((power - turn) * (12000.0 / 127));
}