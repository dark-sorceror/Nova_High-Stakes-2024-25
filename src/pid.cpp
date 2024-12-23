/**
 * \file PID.cpp
 *
 * Updated - 12/15/2024
 * Last Successful Test - 12/15/2024
 */ 

#include <cmath>
#include "api.h"

#include "pid.h"
#include "kalmanFilter.h"

Nova::PID::PID (
    float kP,
    float kI,
    float kD,
    float maxCumulativeError,
    float settleError,
    float settleTime
):
    kP(kP),
    kI(kI),
    kD(kD),
    maxCumulativeError(maxCumulativeError),
    settleError(settleError),
    settleTime(settleTime)
{};

Nova::KalmanFilter kalmanFilter = Nova::KalmanFilter (
    0.0,
    1.0,
    0.0,
    0.01,
    0.1
);

/**
 * @brief Compute the error Robot has from the target
 * 
 * @param error 
 * @return float 
 */
float Nova::PID::compute(float error) {
    float deltaError = error - prevError;

    if (fabs(error) < maxCumulativeError) {
        accumulatedError += error;
    }

    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
        accumulatedError = 0;
    }

    if (accumulatedError > maxIntegral) {
        accumulatedError = maxIntegral;
    } else if (accumulatedError < -maxIntegral) {
        accumulatedError = -maxIntegral;
    }

    /*
    futureError = (error - prevError);

    if (fabs(futureError) > fabs(acceleration + prevDeriv) && prevDeriv != 0) {
        futureError = acceleration + prevDeriv;
    }
    */

    float smoothedError = kalmanFilter.filter(error);

    float smoothedDeriv = alpha * deltaError + (1 - alpha) * prevDeriv;

    output = kP * smoothedError + kI * accumulatedError + kD * smoothedDeriv;

    prevError = smoothedError;
    acceleration = smoothedError - prevDeriv;
    prevDeriv = smoothedDeriv; // futureError

    return output;
}

bool Nova::PID::isSettled() {
    return done;
}

/**
 * @brief Checks whether PID loop is settled
 * 
 * @return true 
 * @return false 
 */
bool Nova::PID::checkIfSettled(float input) {
    const int currentTime = pros::millis();

    if (fabs(input) > settleError) {
        startTime = currentTime;
        done = false;
    }

    if (startTime != -1 && currentTime >= startTime + settleTime) {
        done = true;
    }

    return done;
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
    output = 0;

    startTime = -1;
    done = false;
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

void Nova::PID::setExitConditionConstants (
        float settleError, 
        float settleTime
    ) {

    this -> settleError = settleError;
    this -> settleTime = settleTime;
}