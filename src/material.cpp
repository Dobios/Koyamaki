#include "material.h"

//Constructor for the material object
Material::Material(Vec3f ambient, Vec3f diffuse, Vec3f specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

//Copy constructor
Material::Material(Material const& that) : ambient(that.ambient), diffuse(that.diffuse),
    specular(that.specular), shininess(that.shininess) {}

Material& Material::operator=(Material const& that) {
    this->ambient = that.ambient;
    this->diffuse = that.diffuse;
    this->specular = that.specular;
    this->shininess = that.shininess;

    return (*this);
}