#pragma once

#include <cmath>
#include <iostream>

#include "rtutils.h"

class vec 
{
public:
    vec() : e{0, 0, 0} {}
    vec(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec operator-() const { return vec(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double &operator[](int i) { return e[i]; }

    vec &operator+=(const vec &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec &operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec &operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double length() const
    {
        return sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline double dot(const vec &v)
    {
        return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
    }

    inline vec cross(const vec &v)
    {
        return vec(e[1] * v.e[2] - e[2] * v.e[1],
                   e[2] * v.e[0] - e[0] * v.e[2],
                   e[0] * v.e[1] - e[1] * v.e[0]);
    }

    inline vec normalized()
    {
        double len = (1 / this->length());
        return vec(len * e[0], len * e[1], len * e[2]);
    }

    // Generate random vectors
    inline static vec random() {
        return vec(random_double(), random_double(), random_double());
    }
    inline static vec random(double min, double max){
        return vec(random_double(min, max), random_double(min, max), random_double(min, max));
    }


public:
    double e[3];
};

// Type aliases for vec
using point = vec; // 3D point
using color = vec;  // RGB color

// vec Utility Functions

inline std::ostream &operator<<(std::ostream &out, const vec &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec operator+(const vec &u, const vec &v)
{
    return vec(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec operator-(const vec &u, const vec &v)
{
    return vec(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec operator*(const vec &u, const vec &v)
{
    return vec(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec operator*(double t, const vec &v)
{
    return vec(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec operator*(const vec &v, double t)
{
    return t * v;
}

inline vec operator/(vec v, double t)
{
    return (1 / t) * v;
}

vec random_in_unit_sphere()
{
    while (true)
    {
        vec p = vec::random(-1, 1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}