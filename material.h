#pragma once

#include "ray.h"

// declare struct to get rid of compiler errors
struct hit_info;



class material {
    public:
     virtual bool scatter( const ray& r_in, const hit_info& info, color& attenuation, ray& scattered) const = 0;
};