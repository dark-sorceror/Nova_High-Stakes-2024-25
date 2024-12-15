/**
 * \file auton.h
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
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

            void translate(float dist);
            void rotate(float angle);
            void rotateAbsolute(float angle);
    };
} // namespace Nova

#endif // _AUTON_H_