/**
 * \file pid.h
 *
 * \brief Contains definitions for pid.cpp
 * 
 * \date Updated - 1/6/2025
 */

#ifndef _VELOCITY_H_
#define _VELOCITY_H_

#include <cmath>

#include "api.h"

#include "modules/controllers/pid.h"
#include "modules/controllers/ema.h"

#include "components/chassis.h"

namespace Nova {
    class VelocityController {
        private:
            double target;
            
            PID pid;
            EMA ema;

        public:
            VelocityController(PIDConstants cons, double alpha) : target(0), pid(cons), ema(alpha) {}

            void setVelocity(double v);

            // curr = current velocity (measured), dt = loop time
            double getVoltage(double curr, double dt);
    };

    class VelocityManager {
        private:
            double vl, va;
            double linMin, linMax;
            double angMin, angMax;
            std::optional<double> slew;
            ChassVelocities prev;

        public:
            VelocityManager(
                double vl = 0, 
                double va = 0, 
                double s = 0,
                double linMin = 0, 
                double linMax = 127,
                double angMin = 0, 
                double angMax = 127)
                : vl(vl), va(va), linMin(linMin), linMax(linMax), 
                angMin(angMin), angMax(angMax), prev{0,0}
            {
                if (s != 0) slew = s;
            }

            ChassVelocities update(std::pair<double, double> vals, double dt);

            void setLinMin(double newLinMin);
            void setLinMax(double newLinMax);
            void setAngMin(double newAngMin);
            void setAngMax(double newAngMax);
            void setSlew(double newSlew);
        };
}

#endif