/**
 * \file pid.h
 *
 * \brief Contains definitions for pid.cpp
 * 
 * \date Updated - 1/6/2025
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

#endif