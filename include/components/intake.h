/**
 * \file intake.h
 *
 * \brief Contains definitions for intake.cpp
 * 
 * \date Updated - 9/1/2025
 */

#ifndef _INTAKE_H_
#define _INTAKE_H_

#include "globals.h"

namespace Nova {
    class Intake {
        public:
            void initialize();

            void start(int voltage);
            void stop();

            void raiseIntake();
            void lowerIntake();

            void run();
    };
} // namespace Nova

#endif // _INTAKE_H_