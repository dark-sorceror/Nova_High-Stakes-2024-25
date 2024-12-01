/**
 * \file pid.cpp
 *
 * Updated - 11/30/2024
 * Last Successful Test - 
 */ 

#include "main.h"

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

float Nova::PID::compute(float error) {
    if (fabs(error) < maxCumulativeError) {
        accumulatedError += error;
    }

    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
        accumulatedError = 0;
    }

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
    
    if (fabs(error) < settleError) {
        timeSpentSettled += loopTime;
    } else {
        timeSpentSettled = 0;
    }

    timeSpentRunning += loopTime;

    return output;
}

bool Nova::PID::isSettled() {
    if (timeSpentRunning > timeout && timeout != 0) {
        return true;
    }

    if (timeSpentSettled > settleTime) {
        return true;
    }

    return false;
}

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

void Nova::PID::setExitConditionConstants (
        float settleError, 
        float settleTime, 
        float timeout
    ) {

    this -> settleError = settleError;
    this -> settleTime = settleTime;
    this -> timeout = timeout;
}