/**
 * \file chassis.h
 *
 * \brief Contains drive definitions for chassis.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#ifndef _CHASSIS_H_
#define _CHASSIS_H_

#include "main.h"

namespace Nova {
    class Chassis {
        public:
            void initialize();
            void calibrate();

            /**
             * @brief Get average encoder value of the Chassis
             *
             * @return float
             */
            float getAvgEncoderValue()
            {
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
            float getAvgVelocity()
            {
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
            double getIMURotation()
            {
                return (Nova::imu1.get_rotation() + Nova::imu2.get_rotation()) / 2;
            }

            void resetMotorEncoders()
            {
                drive.tare_position_all();
            }

            void run();

        private:
            /**
             * @brief Change brake mode of Chassis
             *
             * @param brakeMode
             */
            void setBrakeMode(pros::motor_brake_mode_e_t brakeMode)
            {
                drive.set_brake_mode_all(brakeMode);
            }

            /**
             * @brief
             *
             * @param input
             * @return double
             */
            double smooth(double input);

            const int DEADBAND = 10;
        };
}; // namespace Nova

#endif // _CHASSIS_H_