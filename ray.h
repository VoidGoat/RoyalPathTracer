#pragma once

#include "vec.h"

class ray {
public:
    ray() {}
    ray(const point &origin, const vec &direction) : orig(origin), dir(direction) {}

    point origin() const { return orig; }
    vec direction() const { return dir; }

    point at(double dist) const
    {
        return orig + dir * dist;
    }

public:
    point orig;
    vec dir;
};