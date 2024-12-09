#define FMT_HEADER_ONLY
#include "main.h"

Nova::Pose::Pose(float x, float y, float theta) {
    this->x = x;
    this->y = y;
    this->theta = theta;
}

Nova::Pose Nova::Pose::operator+(const Nova::Pose& other) const {
    return Nova::Pose(this->x + other.x, this->y + other.y, this->theta);
}
180-227
0-10 (red)
Nova::Pose Nova::Pose::operator-(const Nova::Pose& other) const {
    return Nova::Pose(this->x - other.x, this->y - other.y, this->theta);
}

float Nova::Pose::operator*(const Nova::Pose& other) const { return this->x * other.x + this->y * other.y; }

Nova::Pose Nova::Pose::operator*(const float& other) const {
    return Nova::Pose(this->x * other, this->y * other, this->theta);
}

Nova::Pose Nova::Pose::operator/(const float& other) const {
    return Nova::Pose(this->x / other, this->y / other, this->theta);
}

Nova::Pose Nova::Pose::lerp(Nova::Pose other, float t) const {
    return Nova::Pose(this->x + (other.x - this->x) * t, this->y + (other.y - this->y) * t, this->theta);
}

float Nova::Pose::distance(Nova::Pose other) const { return std::hypot(this->x - other.x, this->y - other.y); }

float Nova::Pose::angle(Nova::Pose other) const { return std::atan2(other.y - this->y, other.x - this->x); }

Nova::Pose Nova::Pose::rotate(float angle) const {
    return Nova::Pose(this->x * std::cos(angle) - this->y * std::sin(angle),
                        this->x * std::sin(angle) + this->y * std::cos(angle), this->theta);
}