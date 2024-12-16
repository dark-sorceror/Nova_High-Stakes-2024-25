/**
 * \file PID.h
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#ifndef _PID_H_
#define _PID_H_

namespace Nova {
    class PID {
        public:
            /**
             * @brief Construct a new PID object
             * 
             * @param error 
             * @param kP 
             * @param kI 
             * @param kD 
             * @param maxCumulativeError 
             * @param loopTime 
             */
            PID (
                float error,
                float kP,
                float kI,
                float kD,
                float maxCumulativeError,
                float loopTime = 10
            );

            /**
             * @brief Construct a new PID object
             * 
             * @param error 
             * @param kP 
             * @param kI 
             * @param kD 
             * @param maxCumulativeError 
             * @param settleError 
             * @param settleTime 
             * @param timeout 
             * @param loopTime 
             */
            PID (
                float error, 
                float kP, 
                float kI, 
                float kD, 
                float maxCumulativeError,
                float settleError,
                float settleTime,
                float timeout,
                float loopTime = 10
            );

            float kP = 0;
            float kI = 0;
            float kD = 0;

            float dT = 0.2;

            float prevDeriv = 0;
            float acceleration = 0;

            float accumulatedError = 0;
            float maxCumulativeError = 0;
            float futureError = 0;
            float error = 0;
            float prevError = 0;

            float settleTime = 0;
            float settleError = 0;
            float timeSpentSettled = 0;
            float timeSpentRunning = 0;
            float timeout = 0;
            float loopTime = 10;

            float output = 0;

            /**
             * @brief Compute error of Robot from the target position
             * 
             * @param error 
             * @return float 
             */
            float compute(float error);

            /**
             * @brief Check is PID loop is settled
             * 
             * @return true 
             * @return false 
             */
            bool isSettled();

            /**
             * @brief Reset PID loop
             * 
             */
            void reset();

            /**
             * @brief Set PID loop constants
             * 
             * @param kP 
             * @param kI 
             * @param kD 
             * @param maxCumulativeError 
             */
            void setkConstants(
                float kP,
                float kI,
                float kD,
                float maxCumulativeError
            );
            
            /**
             * @brief Set the Exit Condition Constants object
             * 
             * @param settleError 
             * @param settleTime 
             * @param timeout 
             */
            void setExitConditionConstants(
                float settleError,
                float settleTime,
                float timeout
            );
    };
} // namespace Nova

#endif // _PID_H_