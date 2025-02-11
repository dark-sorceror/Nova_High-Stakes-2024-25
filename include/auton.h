/**
 * \file auton.h
 *
 * \brief Contains definitions for auton.cpp
 * 
 * \date Updated - 1/6/2025
 */

#ifndef _AUTON_H_
#define _AUTON_H_

#include "components/chassis.h"
#include "components/intake.h"
#include "components/clamp.h"
#include "components/ladyBrown.h"

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
            Auton(Nova::Chassis chassis, Nova::Intake intake, Nova::Clamp clamp, Nova::LadyBrown ladyBrown);

            /**
             * @brief Blue 1 Elimination Auton Path
             * 
             */
            void test();

            void skills();
            
        private:
            Chassis chassis;
            Intake intake;
            Clamp clamp;
            LadyBrown ladyBrown;
    };
} // namespace Nova

#endif // _AUTON_H_