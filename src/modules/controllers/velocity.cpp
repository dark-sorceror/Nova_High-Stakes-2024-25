#include "modules/controllers/velocity.h"

void Nova::VelocityController::setVelocity(double v) { target = v; }

// curr = current velocity (measured), dt = loop time
double Nova::VelocityController::getVoltage(double curr, double dt) {
    double filtered = ema.filter(curr);
    double error = target - filtered;
    return pid.compute(error, dt);
}

ChassVelocities Nova::VelocityManager::update(std::pair<double, double> vals, double dt) {
    vl = vals.first;
    va = vals.second;

    vl = std::clamp(vl, linMin, linMax);
    va = std::clamp(va, angMin, angMax);

    // apply slew rate if enabled
    if (slew) {
        double maxChange = (*slew) * dt;

        double linDiff = vl - prev.linear;
        if (std::abs(linDiff) > maxChange)
            vl = prev.linear + maxChange * (linDiff > 0 ? 1 : -1);

        double angDiff = va - prev.angular;
        if (std::abs(angDiff) > maxChange)
            va = prev.angular + maxChange * (angDiff > 0 ? 1 : -1);
    }

    prev = {vl, va};
    return prev;
}

void Nova::VelocityManager::setLinMin(double newLinMin) { 
    linMin = newLinMin; 
}

void Nova::VelocityManager::setLinMax(double newLinMax) { 
    linMax = newLinMax; 
}

void Nova::VelocityManager::setAngMin(double newAngMin) { 
    angMin = newAngMin; 
}

void Nova::VelocityManager::setAngMax(double newAngMax) { 
    angMax = newAngMax; 
}

void Nova::VelocityManager::setSlew(double newSlew) { 
    slew = newSlew; 
}