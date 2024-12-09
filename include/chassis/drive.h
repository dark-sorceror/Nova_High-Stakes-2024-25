/**
 * \file drive.h
 *
 * \brief Contains drive definitions for drive.cpp
 * 
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */

#ifndef _DRIVE_H_
#define _DRIVE_H_

namespace Nova {
    class Drive {
        public:
            void initialize();
            void calibrate();

            float getAvgEncoderValue();
            float getAvgVelocity();
            double getIMURotation();

            void run();
        private:
            void resetMotorEncoders();
            void setBrakeMode(pros::motor_brake_mode_e_t);

            void calibrateIMU();

            double smooth(double input);

            const int DEADBAND = 10;
    };
}; // namespace Nova

#endif // _DRIVE_H_