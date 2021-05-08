#pragma once
#include "ray.h"

struct hit_info 
{
    point p;
    vec normal;
    double dist;
};



class traceable
{
    public:
    virtual bool hit(const ray& r, double tmin, double tmax, hit_info& info) const = 0;
};