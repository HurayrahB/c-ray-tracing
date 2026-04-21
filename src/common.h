#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

// C++ std Usings
using std::make_shared;
using std::shared_ptr;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385; // needed for angle calculations

// utility functions
inline double degrees_to_radians(double degrees) {
    return (degrees * pi/ 180.0);
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max) {
    // returns a random real in [min,max)
    return ( min + (max-min)*random_double() );
}
inline int random_int(int min, int max) {
    // returns a random int in [min, max]
    return (int(random_double(min, max+1)));
}

// common headers

#include "colour.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif