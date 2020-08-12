#pragma once
#include "vec3f.h"

class Light {
public:
    Vec3f position;     //The position of the light source
    Vec3f intensity;    //RGB vector defining the intensity of the light source

    Light() = delete;

    //Constructors
    Light(Vec3f position, Vec3f intensity);
    Light(float x, float y, float z, float i_r, float i_g, float i_b);
};