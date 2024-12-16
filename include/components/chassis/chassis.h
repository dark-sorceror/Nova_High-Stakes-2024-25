/**
 * \file chassis.h
 *
 * \brief Contains drive definitions for chassis.cpp
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */

#ifndef _CHASSIS_H_
#define _CHASSIS_H_

namespace Nova {
    class Chassis {
        public:
            /**
             * @brief Initialize chassis
             * 
             */
            void initialize();

            /**
             * @brief Get the Avg Encoder Value object
             * 
             * @return float 
             */
            float getAvgEncoderValue();

            /**
             * @brief Get the Avg Velocity object
             * 
             * @return float 
             */
            float getAvgVelocity();

            /**
             * @brief Get Avg IMU rotation
             * 
             * @return float 
             */
            float getIMURotation();
            
            /**
             * @brief Reset motor encoders of chassis
             * 
             */
            void resetMotorEncoders();

            /**
             * @brief Set the Brake Mode object
             * 
             * @param brakeMode 
             */
            void setBrakeMode(pros::motor_brake_mode_e_t brakeMode);

            /**
             * @brief Calibrate chassis
             * 
             */
            void calibrate();

            /**
             * @brief Run chassis
             * 
             */
            void run();

        private:
            /**
             * @brief Logarthmic drive
             *
             * @param input
             * @return double
             */
            double smooth(double input);
        };
}; // namespace Nova

#endif // _CHASSIS_H_