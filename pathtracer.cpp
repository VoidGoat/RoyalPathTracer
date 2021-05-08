#include <iostream>

#include "vec.h"
#include "color.h"
#include "ray.h"


#include "rtutils.h"

#include "traceable_list.h"
#include "sphere.h"

#include "camera.h"

// return normal if
double hit_sphere(const point& center, double radius, const ray& r)
{
    vec unit_vec = r.direction().normalized();
    vec oc = r.origin() - center;
    double x = unit_vec.dot(oc);
    double del = x * x - (oc.length_squared() - radius * radius);
    if (del > 0)
    {
        return -(unit_vec.dot(oc)) - std::sqrt(del);
    } else 
    {
        return -1.0;
    }
}

color ray_color(const ray& r, const traceable& world, int depth)
{

    if (depth <= 0) {
        return color(0,0,0);
    }

    hit_info info;
    if (world.hit(r, 0.001, 10000, info))
    {
        point target = info.p + info.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(info.p, target - info.p), world, depth - 1);

        // visualize geometry normals
        return 0.5 * (info.normal + color(1,1,1));
    }
    vec unit_dir = r.direction().normalized();
    double val = 0.5 * (unit_dir.y() + 1.0);
    
    // return sky color
    return (1.0 - val) * color(1.0, 1.0, 1.0) + val * color(0.5, 0.7, 1.0);

    // point sphere_center = vec(0, 0, -3.5);
    // double radius = 1;

    // double distance = hit_sphere(sphere_center, radius, r);


    // // return color(r.direction().y(), 0, 0);
    // // return color(std::abs(unit_dir.y()), 0, 0);
    // // return color(unit_dir.y(), 0, 0);

    // if ( distance > 0) {
    //     vec N = (r.at(distance) - sphere_center).normalized();
    //     return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
    // }
    // vec unit_dir = r.direction().normalized();
    // double val = 0.5 * (unit_dir.y() + 1.0);
    // // else
    //     return (1.0 - val) * color(1.0, 1.0, 1.0) + val * color(0.5, 0.7, 1.0);
}

int main()
{


    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    traceable_list world;
    world.add(std::make_shared<sphere>(point(0, 0, -3.5), 1));
    // world.add(std::make_shared<sphere>(point(0, -100, 0), 100));
    world.add(std::make_shared<sphere>(point(2, 0, -4.5), 1));
    world.add(std::make_shared<sphere>(point(-2, 0, -3.5), 0.7));
    world.add(std::make_shared<sphere>(point(0, -101, 0), 100));

    // Camera
    camera cam;
    int a = 0;
    // Render

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remainings: " << j << ' ' << std::flush;
        
        for (int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);


        }
    }
    std::cerr << "Done\n";
}