/**
 * \file kalmanFilter.cpp
 *
 * \brief Contains kalman filtering function
 * 
 * \date Updated - 12/25/2024
 */

#include "kalmanFilter.h"

Nova::KalmanFilter::KalmanFilter (
    float kalmanState,
    float kalmanCovariance,
    float kalmanGain,
    float kalmanProcessNoise,
    float kalmanMeasurementNoise
):
    kalmanState(kalmanState),
    kalmanCovariance(kalmanCovariance),
    kalmanGain(kalmanGain),
    kalmanProcessNoise(kalmanProcessNoise),
    kalmanMeasurementNoise(kalmanMeasurementNoise)
{};

float Nova::KalmanFilter::filter(float measurement) {
    kalmanCovariance += kalmanProcessNoise;

    kalmanGain = kalmanCovariance / (kalmanCovariance + kalmanMeasurementNoise);
    kalmanState += kalmanGain * (measurement - kalmanState);
    kalmanCovariance = (1 - kalmanGain) * kalmanCovariance;

    return kalmanState;
};