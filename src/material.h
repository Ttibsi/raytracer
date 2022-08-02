#ifndef MATERIAL_H
#define MATERIAL_H

#include "constants.h"

struct hit_record;

class Material {
  public:
    virtual bool scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const = 0;
};

class Metal : public Material {
  public:
    color albedo;

    Metal(const color &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const override {

        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

class Lambertian : public Material {
  public:
    color albedo;

    Lambertian(const color &a) : albedo(a) {}

    virtual bool scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const {

        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

#endif
