#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
    public:
        //Attribute
        double e[3];

        // constructors
        vec3() : e{0,0,0} {}
        vec3(double e1, double e2, double e3) : e{e1,e2,e3} {}

        // Getters
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // Overloaded operators
        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[] (int i) const { return e[i]; }
        double& operator[] (int i) { return e[i]; }

        vec3& operator+= (const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*= (const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/= (const doubt t) { return *this *= 1/t; }
 
        // Method signatures
        double length() const { return std:sqrt(length_squared()); }
        double length_squared() const { 
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
};

// Type aliases
using point3 = vec3;
using color = vec3;

#endif
