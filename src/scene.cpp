#include "scene.h"
#include "shape.h"
#include "intersection.h"
#include "ray.h"
#include "light.h"

#include <vector>
#include <memory>

Scene::Scene(Camera const& cam, Light const& light, float ambient, Plane const& plane,Sphere const& sphere) :
    eye(cam), light(light), ambient_lighting(ambient), plane(plane), sphere(sphere), geometry() {}

void Scene::add_sphere(Sphere const& shape) {
    geometry.push_back(make_unique<Sphere>(shape));
}

const Intersection Scene::intersect(Ray const& ray) const {
    Intersection min_intersection(sphere.intersect(ray));

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

    Intersection int_data_2 = plane.intersect(ray);
    if(int_data_2.intersected && int_data_2.intersection_t > 0) {
        if(int_data_2.intersection_t < min_intersection.intersection_t) {
            min_intersection = int_data_2;
        }
    }

    return min_intersection;
}
