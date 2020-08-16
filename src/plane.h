#pragma once

#include "vec3f.h"
#include "intersection.h"
#include "ray.h"
#include "material.h"

class Plane {
private:
    Vec3f surface_point;
    Vec3f normal;
    Material mat;

public:
    Plane() = default;

    //Constructor and copy constructor
    Plane(Vec3f const& surface_point, Vec3f const& normal, Material const& mat);
    Plane(Plane const& other);

    /**
     * @brief Computes the intersection between a given ray and the plane
     * @param ray, the ray with which the intersection will be done
     * @returns the intersection data generated by said intersection
     */
    Intersection intersect(Ray const& ray) const;
};