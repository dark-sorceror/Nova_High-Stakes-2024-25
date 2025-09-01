/**
 * \file chassis.h
 *
 * \brief Contains definitions for chassis.cpp
 * 
 * \date Updated - 3/10/2025
 */

#ifndef _CHASSIS_H_
#define _CHASSIS_H_

#include <cmath>

#include "globals.h"
#include "modules/pose.h"
#include "modules/controllers/pid.h"

struct Point {
    float x;
    float y;
};

struct ChassVelocities {
    double linear;
    double angular;
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
             * @brief Get the Pose object
             * 
             * @param radians 
             * @return Pose 
             */
            Pose getCurrentPosition(bool radians = false);

            /**
             * @brief Set the Pose object
             * 
             * @param pose 
             * @param radians 
             */
            void setPosition(Pose pose, bool radians = false);
            
            /**
             * @brief Tracking Algorithm Loop
             * 
             */
            void updatePosition();

            /**
             * @brief Translate the Robot in x or y directions
             * 
             * @param dist 
             */
            void translate(float dist, int maxSpeed = 120);

            /**
             * @brief Rotate the Robot in 360 degree directions relative to itself
             * 
             * @param angle 
             */
            void rotate(float angle);

            /**
             * @brief 2D PID; Translate and rotate the robot at the same time
             * 
             * @param targetDistance 
             * @param targetHeading 
             * @param timeout 
             * @param resetSensors 
             * @param rushErrorThreshold 
             * @param slewRate 
             */
            void driveAngle(double targetDistance, double targetHeading, double timeout, bool resetSensors, double rushErrorThreshold, double slewRate);

            /**
             * @brief Rotate the Robot in 360 degree directions with 90 as North
             * 
             * @param angle 
             */
            void rotateAbsolute(float angle);

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