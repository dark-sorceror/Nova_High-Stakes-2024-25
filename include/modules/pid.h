/**
 * \file pid.h
 *
 * \brief Contains definitions for pid.cpp
 * 
 * \date Updated - 1/6/2025
 */

#ifndef _PID_H_
#define _PID_H_

#include <cmath>

#include "api.h"

#include "kalmanFilter.h"

namespace Nova {
    class PID {
        public:
            PID (
                float kP, 
                float kI, 
                float kD, 
                float maxCumulativeError,
                float settleError,
                float settleTime
            );

            float compute(float error);

            bool isSettled();

            bool checkIfSettled(float input);

            void reset();

            void setkConstants(
                float kP,
                float kI,
                float kD,
                float maxCumulativeError
            );

            void setExitConditionConstants(
                float settleError,
                float settleTime
            );

        protected:
            float kP = 0;
            float kI = 0;
            float kD = 0;

            float dT = 0.2;

            float prevDeriv = 0;
            float acceleration = 0;

            float accumulatedError = 0;
            float maxCumulativeError = 0;
            float futureError = 0;
            float prevError = 0;
            float maxIntegral = 100;
            float alpha = 0.1;

            float settleTime = 0;
            float settleError = 0;
            float startTime = -1;
            float done = false;

            float output = 0;
    };
} // namespace Nova

#endif // _PID_H_