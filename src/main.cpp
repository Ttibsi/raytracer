#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

/*
 * A PPM file is a type of file that represents an image by specifying
 * every line of pixels, as well as some data at the start that informs the
 * renderer how to display the image.
 *
 * P3 at the start means that its using ascii colours. You then have to specify
 * the size of the image, and the colour space it's using (in our case, 255)
 * and then you can start using RGB triplets to state the colour of each pixel
 *
 * This file needs to be run using at minimum cpp11, and the output is
 * redirected into `image.ppm`, which can be opened in any image viewer.
 */

color ray_color(const ray &r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

void basic_render(int img_width, int img_height) {
    for (int j = img_height - 1; j >= 0; --j) {
        // This is basically a progress indicator
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < img_width; ++i) {
            auto r = double(i) / (img_width - 1);
            auto g = double(j) / (img_height - 1);
            auto b = 0.25;

            // Turn the colour values into ints
            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}

int main() {
    // Create image
    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);

    // Create camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner =
        origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // File renderer
    std::cout << "P3\n" << img_height << ' ' << img_width << "\n255\n";
    // basic_render(img_width, img_height)

    for (int j = img_height - 1; j >= 0; --j) {
        // This is basically a progress indicator
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < img_width; ++i) {
            auto u = double(i) / (img_width - 1);
            auto v = double(j) / (img_height - 1);
            ray r(origin,
                  lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
