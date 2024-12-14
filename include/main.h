/**
 * \file main.h
 *
 * \brief Contains common definitions and header files used throughout your PROS
 * project.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

// PROS
#include "api.h"

// libNova
#include "Subsystems/brain.h"

#include "globals.h"

#include "pose.h"

#include "Subsystems/Chassis/chassis.h"
#include "Subsystems/Chassis/odom.h"

#include "Subsystems/intake.h"
#include "Subsystems/clamp.h"

#include "../renders/logo.c"
#include "../renders/logo_2.c"
#include "../renders/field.c"

LV_IMG_DECLARE(logo);
LV_IMG_DECLARE(logo_2);
LV_IMG_DECLARE(field);

#ifdef __cplusplus
extern "C" {
    #endif
    void autonomous(void);
    void initialize(void);
    void disabled(void);
    void competition_initialize(void);
    void opcontrol(void);
    #ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <iostream>
#include <vector>
#include <numeric>
#endif

#endif  // _PROS_MAIN_H_
