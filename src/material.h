#pragma once

#include "vec3f.h"

class Material {
public:
    Vec3f ambient;  //RGB vector for the material's ambient component
    Vec3f diffuse;  //RGB vector for the material's diffuse component
    Vec3f specular; //RGB vector for the material's specular component
    float shininess;//Cosine exponent that controls the material's shininess

    Material() = delete;

    //Constructor for the material object
    Material(Vec3f ambient, Vec3f diffuse, Vec3f specular, float shininess);

    //Copy constructor
    Material(Material const& that);

    //Overload the = operation to copy the values of a given material into ours
    Material& operator=(Material const& that);
};
