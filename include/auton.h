/**
 * \file auton.h
 *
 * Updated - 1/10/2024
 * Last Successful Test - 1/10/2024
 */ 

#ifndef _AUTON_H_
#define _AUTON_H_

#include "subsystems/Chassis/chassis.h"
#include "subsystems/intake.h"
#include "subsystems/clamp.h"

namespace Nova {
    class Auton {
        public: 
            Auton(Nova::Chassis chassis, Nova::Intake intake, Nova::Clamp clamp);

            void blue1Elims();
        private:
            Chassis chassis;
            Intake intake;
            Clamp clamp;

            //void trackPosition(int left, int right);
            void translate(float dist);
            void rotate(float angle);
            void rotateAbsolute(float angle);
            void swerveLeft(float dist, float angle);
            void swerveRight(float dist, float angle);
    };
}

#endif