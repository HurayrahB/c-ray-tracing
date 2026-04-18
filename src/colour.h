#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include "interval.h"
#include "vec3.h"

using colour = vec3;

void write_colour(std::ostream& out, const colour& pixel_colour) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    // translate the [0,1] component values to byte range
    static const interval intensity (0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // write out the pixel colour components
    out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ' << '\n';
}

#endif