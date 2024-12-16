/**
 * \file auton.h
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#ifndef _AUTON_H_
#define _AUTON_H_

#include "components/chassis/chassis.h"
#include "components/intake.h"
#include "components/clamp.h"

namespace Nova {
    class Auton {
        public: 
            /**
             * @brief Construct a new Auton object
             * 
             * @param chassis 
             * @param intake 
             * @param clamp 
             */
            Auton(Nova::Chassis chassis, Nova::Intake intake, Nova::Clamp clamp);

            /**
             * @brief Blue 1 Elimination Auton Path
             * 
             */
            void blue1Elims();
        private:
            Chassis chassis;
            Intake intake;
            Clamp clamp;

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
    };
} // namespace Nova

#endif // _AUTON_H_