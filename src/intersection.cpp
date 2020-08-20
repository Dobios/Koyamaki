#include "intersection.h"

//Default constructor
Intersection::Intersection() : point(), normal(), dir_to_eye(), material(),
    intersection_t(NO_INTERSECTION), intersected(false) {}

//Constructor
Intersection::Intersection(
    Vec3f const& point,
    Vec3f const& normal,
    Vec3f const& dir_to_eye,
    Material const& material,
    float intersection_t,
    bool intersected
) : point(point), normal(normal.normalized()), dir_to_eye(dir_to_eye.normalized()),
    material(material), intersection_t(intersection_t), intersected(intersected) {}

//Copy constructor
Intersection::Intersection(Intersection const& that) : 
    point(that.point), normal(that.normal.normalized()), dir_to_eye(dir_to_eye.normalized()),
    material(that.material), intersection_t(that.intersection_t), intersected(that.intersected) {}

Intersection const& Intersection::operator=(Intersection const& other) {
    point = other.point;
    normal = other.normal;
    dir_to_eye = other.dir_to_eye;
    material = other.material;
    intersection_t = other.intersection_t;
    intersected = other.intersected;

    return (*this);
}