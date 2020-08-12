#pragma once

#include "vec3f.h"
#include "intersection.h"
#include "light.h"

//Represents an RGB color vector
typedef Vec3f Color;

class Shader {
public:
    /**
     * @brief Computes the phong shading of a given intersection using a single light source
     * @param int_data, the intersection data from a successful intersection
     * @param light, the single point light_source that will illuminate our object
     * @param ambient the ambient light intensity in the scene
     * @returns the color of the the intersected point
     */
    static Color shade_point(Intersection const& int_data, Light const& light, float const& ambient);
};