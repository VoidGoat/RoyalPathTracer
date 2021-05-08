#pragma once
#include "traceable.h"

class sphere : public traceable
{
public:
    sphere() {}
    sphere(point cen, double rad) : center(cen), radius(rad) {}
    ~sphere() {}

    virtual bool hit(const ray &r, double tmin, double tmax, hit_info &info) const override;

public:
    point center;
    double radius;
};



bool sphere::hit(const ray &r, double tmin, double tmax, hit_info &info) const
{
    vec oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = oc.dot(r.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return false;
    }
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b - sqrtd) / a;
    if (root < tmin || tmax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < tmin || tmax < root) {
            return false;
        }
    }

    info.dist = root;
    info.p = r.at(info.dist);
    info.normal = (info.p - center) / radius;

    return true;
}