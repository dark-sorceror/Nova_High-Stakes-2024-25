/**
 * \file auton.h
 *
 * \brief Contains definitions for auton.cpp
 * 
 * \date Updated - 12/25/2024
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
            void test();
        private:
            Chassis chassis;
            Intake intake;
            Clamp clamp;
    };
} // namespace Nova

#endif // _AUTON_H_