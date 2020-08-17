#include "shader.h"
#include "scene.h"
#include "vec3f.h"
#include "ray.h"

#include <math.h>
#include <memory>

const Color Shader::shade_point(Intersection const& int_data, unique_ptr<Scene> const& scene) {
    if(!(int_data.intersected)) {
        return Color(0.1f);
    }

    //Compute the direction to the light, normal, eye, and reflected ray
    const Vec3f l((scene->light.position - int_data.point).normalized());
    const Vec3f n(int_data.normal);

    //Used for the specular reflection
    const Vec3f v(int_data.dir_to_eye.normalized());
    const Vec3f r((Vec3f(2 * n.dot(l)) * n - l).normalized());

    //Compute the ambient color of the point
    const Color ambient_color(int_data.material.ambient * scene->ambient_lighting);

    //Compute the diffuse & specular colors of the point
    const float cos_theta = max(n.dot(l), 0.f);
    const float cos_alpha = max(pow(r.dot(v), int_data.material.shininess), 0.f);

    const Color diffuse_color(scene->light.intensity * int_data.material.diffuse * Vec3f(cos_theta));
    const Color specular_color(scene->light.intensity * int_data.material.specular * Vec3f(cos_alpha));

    //Check for shadows
    const Color diff_spec = is_shadow(int_data.point, int_data.normal, l, scene) ?
        Vec3f(0.f) : (diffuse_color + specular_color);

    return (ambient_color + diff_spec).min(Vec3f(1.f));
}

const bool Shader::is_shadow(Vec3f const& point, Vec3f const& normal, Vec3f const& dir_to_light, unique_ptr<Scene> const& scene) {
    //Generate a shadow ray from the given point
    const Ray shadow_ray(point + (normal * Vec3f(EPSILON)), dir_to_light, true);

    //Shoot ray towards light and check for intersection
    const Intersection int_data(scene->intersect(shadow_ray));

    //Check for any intersection
    return int_data.intersected;
}