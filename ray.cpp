#include "ray.h"

Ray::Ray(Vec3f const& origin, Vec3f const& direction, bool shadow_ray) :
    origin(origin), direction(direction), shadow_ray(shadow_ray) {}

Ray::Ray(Ray const& ray) : origin(ray.origin), direction(ray.direction), shadow_ray(ray.shadow_ray) {}

//Getters
Vec3f const& Ray::get_origin() const {
    return this->origin;
}

Vec3f const& Ray::get_direction() const {
    return this->direction;
}

bool Ray::is_shadow_ray() const {
    return this->shadow_ray;
}

//Evaluates the result of r(t) = o + t*d
Vec3f Ray::operator()(float t) const {
    return get_origin() + Vec3f(t) * get_direction();
}