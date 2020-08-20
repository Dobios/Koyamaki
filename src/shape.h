#pragma once

#include "intersection.h"
#include "ray.h"

class Shape {
public:
    virtual ~Shape() = default;
    virtual const Intersection intersect(Ray const& ray) const = 0;
};
