#include "scene.h"
#include "shape.h"
#include "intersection.h"
#include "ray.h"
#include "light.h"

#include <vector>
#include <memory>

Scene::Scene(Camera const& cam, Light const& light, float ambient) :
    eye(cam), light(light), ambient_lighting(ambient), geometry() {}

void Scene::add_sphere(Sphere const& shape) {
    geometry.push_back(make_unique<Sphere>(shape));
}

void Scene::add_plane(Plane const& shape) {
    geometry.push_back(make_unique<Plane>(shape));
}

const Intersection Scene::intersect(Ray const& ray) const {
    float intersection_t(NO_INTERSECTION);
    bool intersection(false);
    Vec3f intersection_point;
    Vec3f intersection_normal;
    Vec3f dir_to_eye;
    Material intersected_material(NO_MATERIAL);
    Intersection min_intersection(
        intersection_point,
        intersection_normal,
        dir_to_eye,
        intersected_material,
        intersection_t,
        intersection
    );

    //Test the intersection against everything
    for(auto const& shape : geometry) {
        const Intersection int_data = shape->intersect(ray);

        //Check to see if we hit something
        if(int_data.intersected && int_data.intersection_t > 0) {
            //Is the new intersection closer along the ray
            if(int_data.intersection_t < min_intersection.intersection_t) {
                min_intersection = int_data;
            }
        } 
    }

    return min_intersection;
}
