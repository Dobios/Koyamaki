#pragma once

#include "vec3f.h"
#include "shape.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"
#include "light.h"
#include "intersection.h"
#include "ray.h"

#include <vector>
#include <memory>

using namespace std;

class Scene {
private:
    vector<unique_ptr<Sphere>> geometry;
    const Sphere sphere;
    const Plane plane;
    const Camera eye;

public:
    const Light light;
    const float ambient_lighting;

public:
    Scene() = delete;
    Scene(Scene const& other) = delete;

    /**
     * @brief Constructor for the scene class
     * @param cam, the main camera of the scene
     * @param light, the only light in the scene
     * @param ambient, the intensity of the ambien light in the scene
     * @note the geometry must be added after construction
     */
    Scene(Camera const& cam, Light const& light, float ambient, Plane const& plane, Sphere const& sphere);

    /**
     * @brief Adds a given sphere to the scene 
     * @param shape, the shape that will be added to the scene
     */
    void add_sphere(Sphere const& shape);

    /**
     * @brief Computes the closest intersection between a given ray and the geometry in the scene
     * @param ray, the ray that will be tested against every object in the scene
     * @returns the closest intersection on the ray's path
     */
    const Intersection intersect(Ray const& ray) const;
};