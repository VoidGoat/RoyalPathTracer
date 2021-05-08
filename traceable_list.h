#pragma once

#include "traceable.h"

#include <vector>
#include <memory>

using std::shared_ptr;

class traceable_list : public traceable
{
public:
    traceable_list() {}
    traceable_list(shared_ptr<traceable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<traceable> object) { objects.push_back(object); }

    virtual bool hit(
        const ray &r, double t_min, double t_max, hit_info &info) const override;

private:
    std::vector<shared_ptr<traceable>> objects;
};


bool traceable_list::hit(const ray &r, double t_min, double t_max, hit_info &info) const
{
    hit_info temp_info;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_info))
        {
            hit_anything = true;
            closest_so_far = temp_info.dist;
            info = temp_info;
        }
    }

    return hit_anything;
}