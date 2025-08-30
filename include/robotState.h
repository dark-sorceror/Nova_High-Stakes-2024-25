/**
 * \file robotState.h
 *
 * \brief Contains definitions for robotState.cpp
 * 
 * \date Updated - 3/10/2025
 */ 

#ifndef _ROBOT_STATE_H_
#define _ROBOT_STATE_H_

#include "pros/rtos.hpp"

#include "components/ladyBrown/ladyBrown.h"

namespace Nova {
    class RobotState {
    public:
        static RobotState* instance;
        static RobotState* getInstance() {
            if (instance == nullptr) {
                instance = new RobotState();
            }

            return instance;
        }

        LadyBrownState getLadyBrownState();
        void setLadyBrownState(LadyBrownState state);

    private:
        pros::Mutex mutex;
        RobotState() = default;
        LadyBrownState ladyBrownState = LadyBrownState::idle;
    };
} // namespace Nova

#endif // _ROBOT_STATE_H_