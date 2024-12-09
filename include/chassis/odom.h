#pragma once

#include "main.h"

namespace Nova {

Pose getPose(bool radians = false);

void setPose(Pose pose, bool radians = false);

void update();

void init();
} // namespace Nova