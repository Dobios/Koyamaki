#pragma once

#include "intersection.h"
#include "ray.h"

class Shape {
public:
    virtual ~Shape() = 0;
    virtual const Intersection intersect(Ray const& ray) const = 0;
};
