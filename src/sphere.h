#pragma once

#include "vec3f.h"
#include "material.h"
#include "ray.h"
#include "intersection.h"
#include "shape.h"

class Sphere : public Shape {
public:
    Vec3f center;
    float radius;
    Material mat;

    Sphere() = delete;
    virtual ~Sphere() = default;

    //Constructor
    Sphere(Vec3f const& center, float radius, Material const& mat);

    //Copy constructor
    Sphere(Sphere const& that);

    /**
     * @brief Computes the intersection between a given ray and the sphere
     * @param ray, a ray with which we will be intersecting
     * @returns the point at which the intersection happened
     */
    virtual const Intersection intersect(Ray const& ray) const;
};