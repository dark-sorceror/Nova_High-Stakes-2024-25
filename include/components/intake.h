/**
 * \file intake.h
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#ifndef _INTAKE_H_
#define _INTAKE_H_

namespace Nova {
    class Intake {
        public:
            void initialize();

            void spinFor(int seconds);

            void run();
    };
} // namespace Nova

#endif // _INTAKE_H_