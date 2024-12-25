/**
 * \file intake.h
 *
 * \brief Contains definitions for intake.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _INTAKE_H_
#define _INTAKE_H_

namespace Nova {
    class Intake {
        public:
            void initialize();
            void start();
            void stop();
            void run();
    };
} // namespace Nova

#endif // _INTAKE_H_