/**
 * \file kalmanFilter.h
 *
 * \brief Contains definitions for kalmanFilter.cpp
 * 
 * \date Updated - 12/25/2024
 */

#ifndef _KALMANFILTER_H_
#define _KALMANFILTER_H_

namespace Nova {
    class KalmanFilter {
        public:
            KalmanFilter (
                float kalmanState,
                float kalmanCovariance,
                float kalmanGain,
                float kalmanProcessNoise,
                float kalmanMeasurementNoise
            );

            float filter(float measurement);
        
        protected:
            float kalmanState = 0.0;
            float kalmanCovariance = 1.0;
            float kalmanGain = 0.0;
            float kalmanProcessNoise = 0.01;
            float kalmanMeasurementNoise = 0.1;
    };
}; // namespace Nova

#endif // _KALMANFILTER_H_