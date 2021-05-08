#pragma once

#include "rtutils.h"
#include "ray.h"
#include "vec.h"

class camera {
    public:
        camera() {
            double aspect_ratio = 16.0 / 9.0;

            double viewport_height = 1.0;
            double viewport_width = viewport_height * aspect_ratio;
            double focal_length = 1.0;
 
            origin = point(0, 0, 0);
            horizontal = vec(viewport_width, 0, 0);
            vertical = vec(0, viewport_height, 0);
            lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec(0, 0, focal_length);
        }

        ray get_ray(double u, double v) {
            return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
        }

    private:
        // Camera position origin
        point origin;
        
        // lower left corner of view plane
        point lower_left_corner;
        
        // horizontal vector
        vec horizontal;
        //
        vec vertical;
};