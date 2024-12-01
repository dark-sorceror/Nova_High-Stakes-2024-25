/**
 * \file drive.h
 *
 * Updated - 11/30/2024
 * Last Successful Test - 11/30/2024
 */ 

#ifndef __DRIVE
#define __DRIVE

namespace Nova {
    class Drive {
        public:
            void initialize();
            void autonInitialize();
            void resetMotorEncoders();
            void resetIMU();
            float getAvgEncoderValue();
            float getAvgVelocity();
            double getIMURotation();
            double smooth(double input);
            void run();
        private:
            const int DEADBAND = 10;
    };
}

#endif