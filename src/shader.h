#pragma once

#include "vec3f.h"
#include "intersection.h"
#include "light.h"
#include "scene.h"

#include <memory>

#define EPSILON 0.02

//Represents an RGB color vector
typedef Vec3f Color;

class Shader {
public:
    /**
     * @brief Computes the phong shading of a given intersection using a single light source
     * @param int_data, the intersection data from a successful intersection
     * @param scene, the scene in which the point shall be shaded
     * @returns the color of the the intersected point
     */
    static const Color shade_point(Intersection const& int_data, unique_ptr<Scene> const& scene);

    /**
     * @brief Computes whether a given point is in a shadow or not
     * @param point, the point which we want to check
     * @param normal, the intersection normal used to get avoid shadow acne
     * @param dir_to_light, the normalized direction to the light which we are testing for
     * @param scene, the scene in which the point shall be tested
     * @returns true if the point is in a shadow, false otherwise
     */
    static const bool is_shadow(Vec3f const& point, Vec3f const& normal, Vec3f const& dir_to_light, unique_ptr<Scene> const& scene);
};