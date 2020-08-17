#include "plane.h"
#include "vec3f.h"
#include "intersection.h"
#include "ray.h"

Plane::Plane(Vec3f const& surface_point, Vec3f const& normal, Material const& mat) :
    surface_point(surface_point), normal(normal.normalized()), mat(mat) {}

Plane::Plane(Plane const& other) : surface_point(other.surface_point),
    normal(other.normal.normalized()), mat(other.mat) {}

const Intersection Plane::intersect(Ray const& ray) const {
    //Compute d component of the cartesian equation n_0 * x + n_1 * y + n_2 * z = d
    float d(normal.dot(surface_point));

    //Initialize our intersection data
    float intersection_t(NO_INTERSECTION);
    bool intersection(false);
    Vec3f intersection_point;
    Vec3f intersection_normal;
    Vec3f dir_to_eye;
    Material intersected_material(NO_MATERIAL);

    //Compute the intersection t by solving the cartesiant equation
    float divid(ray.get_direction().dot(normal));

    //Check that a solution exists
    if(divid != 0.f) {
        const float solution = (d - ray.get_origin().dot(normal)) / divid;

        //Check that the intersection isn't behind the camera
        if(solution > 0.f) {
            intersection_t = solution;
        }
    }

    if(intersection_t != NO_INTERSECTION) {
        intersection_point = ray(intersection_t);
        intersection_normal = normal;
        dir_to_eye = (intersection_point - ray.get_origin()).normalized();
        intersected_material = mat;
        intersection = true;
    }

    return Intersection(
        intersection_point,
        intersection_normal,
        dir_to_eye,
        intersected_material,
        intersection_t,
        intersection
    );
}
