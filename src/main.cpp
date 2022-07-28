#include <iostream>

#include "color.h"
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
    const int img_height = 256;
    const int img_width = 256;

    // File renderer
    std::cout << "P3\n" << img_height << ' ' << img_width << "\n255\n";
    //basic_render(img_width, img_height)

    for (int j = img_height - 1; j >= 0; --j) {
        // This is basically a progress indicator
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < img_width; ++i) {
            color pixel_color(double(i)/(img_width-1), double(j)/(img_height-1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
