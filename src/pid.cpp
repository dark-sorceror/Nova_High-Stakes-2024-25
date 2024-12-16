/**
 * \file PID.cpp
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#include <cmath>

#include "pid.h"

/**
 * @brief Construct a new Nova::PID::PID object
 * 
 * @param error 
 * @param kP 
 * @param kI 
 * @param kD 
 * @param maxCumulativeError 
 * @param loopTime 
 */
Nova::PID::PID (
        float error,
        float kP, 
        float kI,
        float kD,
        float maxCumulativeError,
        float loopTime
    ):

    error(error),
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    loopTime(loopTime)
{};

/**
 * @brief Construct a new Nova:: PID::PID object
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
Nova::PID::PID (
        float error,
        float kP,
        float kI,
        float kD,
        float maxCumulativeError,
        float settleError,
        float settleTime,
        float timeout,
        float loopTime
    ):

    error(error),
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    settleError(settleError),
    settleTime(settleTime),
    timeout(timeout),
    loopTime(loopTime)
{};

/**
 * @brief Compute the error Robot has from the target
 * 
 * @param error 
 * @return float 
 */
float Nova::PID::compute(float error) {
    if (fabs(error) < maxCumulativeError) accumulatedError += error;

    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) accumulatedError = 0;

    /*
    futureError = (error - prevError);

    if (fabs(futureError) > fabs(acceleration + prevDeriv) && prevDeriv != 0) {
        futureError = acceleration + prevDeriv;
    }
    */

    output = kP * error + kI * accumulatedError + kD * (error - prevError);

    prevError = error;
    acceleration = futureError - prevDeriv;
    prevDeriv = futureError;
    
    if (fabs(error) < settleError) timeSpentSettled += loopTime;
    else timeSpentSettled = 0;

    timeSpentRunning += loopTime;

    return output;
}

/**
 * @brief Checks whether PID loop is settled
 * 
 * @return true 
 * @return false 
 */
bool Nova::PID::isSettled() {
    if (timeSpentRunning > timeout && timeout != 0) return true;

    if (timeSpentSettled > settleTime) return true;

    return false;
}

/**
 * @brief Reset PID loop
 * 
 */
void Nova::PID::reset() {
    accumulatedError = 0;
    futureError = 0;
    prevError = 0;

    acceleration = 0;
    prevDeriv = 0;
    error = 0;
    output = 0;

    timeSpentSettled = 0;
    timeSpentRunning = 0;
}

/**
 * @brief Setting the PID Constants
 * 
 * @param kP 
 * @param kI 
 * @param kD 
 * @param maxCumulativeError 
 */
void Nova::PID::setkConstants (
        float kP, 
        float kI, 
        float kD, 
        float maxCumulativeError
    ) {

    this -> kP = kP;
    this -> kI = kI;
    this -> kD = kD;
    this -> maxCumulativeError = maxCumulativeError;
} 

/**
 * @brief Setting the Exit Condition Constants
 * 
 * @param settleError 
 * @param settleTime 
 * @param timeout 
 */
void Nova::PID::setExitConditionConstants (
        float settleError, 
        float settleTime, 
        float timeout
    ) {

    this -> settleError = settleError;
    this -> settleTime = settleTime;
    this -> timeout = timeout;
}