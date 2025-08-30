/**
 * \file ema.cpp
 *
 * \brief Contains EMA
 * 
 * \date Updated - 8/30/2025
 */

#include "modules/controllers/ema.h"

double Nova::EMA::filter(double input) {
    if (!initialized) {
        filtered = input;
        initialized = true;
    } else {
        filtered = alpha * input + (1 - alpha) * filtered;
    }
    
    return filtered;
}