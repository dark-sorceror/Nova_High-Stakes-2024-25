/**
 * \file ema.h
 *
 * \brief Contains definitions for ema.cpp
 * 
 * \date Updated - 8/30/2025
 */

#ifndef _EMA_H_
#define _EMA_H_

#include <cmath>

#include "api.h"

#include "modules/controllers/pid.h"

namespace Nova {
    class EMA {
        double alpha;
        bool initialized;
        double filtered;

        public:
            EMA(double alpha) : alpha(alpha), initialized(false), filtered(0) {}

            double filter(double input);
        };
};

#endif // _EMA_H_