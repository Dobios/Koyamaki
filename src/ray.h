#pragma once

#include "vec3f.h"

class Ray {
private:
    Vec3f origin;
    Vec3f direction;
    bool shadow_ray;

public:
    //Constructor for the Ray
    Ray(Vec3f const& origin, Vec3f const& direction, bool shadow_ray = false);

    //Copy constructor
    Ray(Ray const& ray);

    //Getters
    Vec3f const& get_origin() const;
    Vec3f const& get_direction() const;
    const bool is_shadow_ray() const;

    //Evaluates the result of r(t) = o + t*d
    const Vec3f operator()(float t) const;
};