#pragma once

#include "intersection.h"
#include "ray.h"

class Shape {
public:
    virtual const Intersection intersect(Ray const& ray) const = 0;
};
