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
    Intersection min_intersection;

    //Test the intersection against everything
    Intersection int_data;
    for(auto const& shape : geometry) {
        int_data = shape->intersect(ray);
        
        //Is the new intersection closer along the ray
        if(int_data.intersection_t < min_intersection.intersection_t) {
            min_intersection = int_data;
        }
    }

    return min_intersection;
}
