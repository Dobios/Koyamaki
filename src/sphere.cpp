#include <array>
#include <limits>
#include <iostream>

#include "sphere.h"
#include "solver.h"
#include "vec3f.h"
#include "material.h"

#define NO_INTERSECTION numeric_limits<float>::max()
#define NO_MATERIAL Material(Vec3f(0.f), Vec3f(0.f), Vec3f(0.f), 0.0)

using namespace std;

//Constructor
Sphere::Sphere(Vec3f const& center, float radius, Material const& mat) :
    center(center), radius(radius), mat(mat) {}

//Copy constructor
Sphere::Sphere(Sphere const& that) : center(that.center), radius(that.radius),
    mat(that.mat) {}

/**
 * @brief Computes the intersection between a given ray and the sphere
 * @param ray, a ray with which we will be intersecting
 * @returns the point at which the intersection happened
 */
const Intersection Sphere::intersect(Ray const& ray) const {
    Vec3f const oc(ray.get_origin() - this->center);

    //The three coefficients of our implicit sphere equation
    float a(ray.get_direction().dot(ray.get_direction()));
    float b(2 * ray.get_direction().dot(oc));
    float c(oc.dot(oc) - (radius * radius));

    //Where our solutions will be stored
    array<float, 2> t;

    //Solve our implicit equation
    size_t num_solutions(Solver::solve_quadratic(a, b, c, t));

    //Initialize our intersection data
    float intersection_t(NO_INTERSECTION);
    bool intersection(true);
    Vec3f intersection_point(ray(intersection_t));
    Vec3f intersection_normal;
    Material intersected_material(NO_MATERIAL);

    for(int i(0); i < num_solutions; ++i) {
        const float solution_t = t[i];

        //Check that t is indeed in front of the camera
        if(solution_t <= 0 && solution_t < intersection_t) {
            intersection_t = solution_t;
        } 
    }

    if(intersection_t == NO_INTERSECTION) {
        intersection = false;
    } else {
        //Compute the final intersection data
        intersection_point = ray(intersection_t);
        intersection_normal = (intersection_point - this->center) / this->radius;
        intersected_material = this->mat;
    }

    return Intersection(intersection_point, intersection_normal, intersected_material, intersection_t, intersection);
}