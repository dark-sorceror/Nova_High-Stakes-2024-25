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