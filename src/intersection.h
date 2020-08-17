#pragma once

#include "vec3f.h"
#include "material.h"

#define NO_INTERSECTION numeric_limits<float>::max()

class Intersection {
public:
    Vec3f point;            //The point at which the intersection happened 
    Vec3f normal;           //The normal of the intersection
    Vec3f dir_to_eye;       //The normalized direction to the eye from the intersection point
    Material material;      //The material of the intersected point
    float intersection_t;   //At which point along the ray the intersection happened
    bool intersected;       //Whether the intersection is valid or not

    Intersection() = delete;

    //Constructor
    Intersection(
        Vec3f const& point,
        Vec3f const& normal,
        Vec3f const& dir_to_eye,
        Material const& material,
        float intersection_t,
        bool intersected
    );

    //Copy constructor
    Intersection(Intersection const& that);

    //Custom assignement operator
    Intersection const& operator=(Intersection const& other);
};