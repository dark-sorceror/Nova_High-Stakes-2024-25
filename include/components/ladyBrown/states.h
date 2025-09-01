/**
 * \file states.h
 *
 * \brief Contains ladybrown states
 * 
 * \date Updated - 8/31/2025
 */ 

#ifndef _STATES_H_
#define _STATES_H_

#include "pros/rtos.hpp"

#include "components/ladyBrown/ladyBrown.h"

namespace Nova {
    enum class LadyBrownState {
        firstRing, 
        secondRing,
        score,
        hang,
        remove, 
        close,
    };

    class State {
        public:
            static State* instance;

            static State* getInstance() {
                if (instance == nullptr) {
                    instance = new State();
                }

                return instance;
            }

            LadyBrownState getLadyBrownState();

            void setLadyBrownState(LadyBrownState state);

        private:
            pros::Mutex mutex;

            State() = default;

            LadyBrownState ladyBrownState = LadyBrownState::close;
    };
} // namespace Nova

#endif // _STATES_H_