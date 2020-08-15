#include "shader.h"
#include "vec3f.h"

#include <math.h>

Color Shader::shade_point(Intersection const& int_data, Light const& light, float const& ambient) {
    if(!(int_data.intersected)) {
        return Color(0.1f);
    }

    //Compute the direction to the light, normal, eye, and reflected ray
    Vec3f l((light.position - int_data.point).normalized());
    Vec3f n(int_data.normal);

    //Used for the specular reflection
    Vec3f v(int_data.dir_to_eye.normalized());
    Vec3f r(Vec3f(2 * n.dot(l)) * n - l);

    //Compute the ambient color of the point
    Color ambient_color(int_data.material.ambient * ambient);

    //Compute the diffuse color of the point
    float cos_theta = n.dot(l);
    if(cos_theta < 0.f) {
        cos_theta = 0.f;
    }

    float cos_alpha = pow(r.dot(v), int_data.material.shininess);
    if(cos_alpha < 0.f) {
        cos_alpha = 0.f;
    }

    Color diffuse_color(light.intensity * int_data.material.diffuse * Vec3f(cos_theta));

    Color specular_color(light.intensity * int_data.material.specular * Vec3f(cos_alpha));

    return (ambient_color + diffuse_color + specular_color).min(Vec3f(1.f));
}