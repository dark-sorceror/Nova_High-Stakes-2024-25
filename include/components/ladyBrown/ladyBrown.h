/**
 * \file ladyBrown.h
 *
 * \brief Contains definitions for ladyBrown.cpp
 * 
 * \date Updated - 2/10/2025
 */

#ifndef _LADYBROWN_H_
#define _LADYBROWN_H_

#include "pros/misc.h"
#include "pros/rtos.hpp"

#include "globals.h"
#include "components/intake.h"

#include "ladyBrown/states.h"

namespace Nova {
    class LadyBrown {
        public:
            void goToPosition(float position);
            void initialize();
            void run();
            void next();
            void prev();
            void toggle();
            void score();
            void setState(LadyBrownState newState);
            void setTarget(LadyBrownState state);
            void startControl();
            void spin(double voltage);
            void setControl(bool on);
            void calibrate();

        private:
            pros::Motor *motor;
            pros::Rotation *rot;
            pros::Optical *optical;
            pros::Task *task = nullptr;

            std::unordered_map<LadyBrownState, LadyBrownState> fwdMap = {
                {LadyBrownState::firstRing, LadyBrownState::secondRing},
                {LadyBrownState::secondRing, LadyBrownState::score},
                {LadyBrownState::score, LadyBrownState::hang},
                {LadyBrownState::hang, LadyBrownState::remove},
                {LadyBrownState::remove, LadyBrownState::close},
                {LadyBrownState::close, LadyBrownState::firstRing}
            };

            std::unordered_map<LadyBrownState, LadyBrownState> revMap = {
                {LadyBrownState::secondRing, LadyBrownState::firstRing},
                {LadyBrownState::score, LadyBrownState::secondRing},
                {LadyBrownState::hang, LadyBrownState::score},
                {LadyBrownState::remove, LadyBrownState::hang},
                {LadyBrownState::close, LadyBrownState::remove},
                {LadyBrownState::firstRing, LadyBrownState::close}
            };

            std::unordered_map<LadyBrownState, double> valueMap = {
                {LadyBrownState::firstRing, 181.5},
                {LadyBrownState::secondRing, 197},
                {LadyBrownState::score, 350},
                {LadyBrownState::hang, 500},
                {LadyBrownState::remove, 180},
                {LadyBrownState::close, 600}
            };
            
            LadyBrownState currentState;
    };
} // namespace Nova

#endif // _LADYBROWN_H_