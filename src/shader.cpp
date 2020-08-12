#include "shader.h"
#include "vec3f.h"

Color Shader::shade_point(Intersection const& int_data, Light const& light, float const& ambient) {
    if(!(int_data.intersected)) {
        return Color(0.1f);
    }

    //Compute the direction to the light
    Vec3f l((light.position - int_data.point).normalized());
    Vec3f n(int_data.normal.normalized());

    //Compute the ambient color of the point
    Color ambient_color(int_data.material.ambient * ambient);

    //Compute the diffuse color of the point
    float cos_theta = n.dot(l);

    Color diffuse_color(light.intensity * int_data.material.diffuse * Vec3f(cos_theta));

    return ambient_color + diffuse_color;
}