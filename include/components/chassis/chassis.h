/**
 * \file chassis.h
 *
 * \brief Contains definitions for chassis.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _CHASSIS_H_
#define _CHASSIS_H_

struct Point {
    float x;
    float y;
};


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
             * @brief Translate the Robot in x or y directions
             * 
             * @param dist 
             */
            void translate(float dist);

            /**
             * @brief Rotate the Robot in 360 degree directions relative to itself
             * 
             * @param angle 
             */
            void rotate(float angle);

            /**
             * @brief Rotate the Robot in 360 degree directions with 90 as North
             * 
             * @param angle 
             */
            void rotateAbsolute(float angle);

            void followPath(const std::vector<Point> &waypoints);

            /**
             * @brief Run chassis
             * 
             */
            void run();

        private:
            /**
             * @brief Set the Brake Mode object
             * 
             * @param brakeMode 
             */
            void setBrakeMode(pros::motor_brake_mode_e_t brakeMode);

            /**
             * @brief Reset motor encoders of chassis
             * 
             */
            void resetMotorEncoders();

            void resetIMUs();

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