#include "light.h"

//Constructors
Light::Light(Vec3f position, Vec3f intensity) : position(position), intensity(intensity) {}

Light::Light(float x, float y, float z, float i_r, float i_g, float i_b) :
    position(x, y, z), intensity(i_r, i_g, i_b) {}