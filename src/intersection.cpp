#include "intersection.h"

//Constructor
Intersection::Intersection(Vec3f const& point, Vec3f const& normal, Material const& material, float intersection_t, bool intersected) :
    point(point), normal(normal), material(material), intersection_t(intersection_t), intersected(intersected) {}

//Copy constructor
Intersection::Intersection(Intersection const& that) : 
    point(that.point), normal(that.normal), material(that.material),
    intersection_t(that.intersection_t), intersected(that.intersected) {}