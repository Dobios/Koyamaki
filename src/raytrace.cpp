#include <iostream>
#include <fstream>
#include <array>
#include <string>

#include "vec3f.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "shader.h"
#include "light.h"
#include "camera.h"

using namespace std;

int main(void) {
    const unsigned int width = 1920;
    const unsigned int height = 1080;

    array<array<string, height>, width>* pixels = new array<array<string, height>, width>();

    //Create the scene (static so everything is const)
    const Sphere sphere(Vec3f(0, 1, 5), 2, Material(Vec3f(1.f, 0.0, 0.8), Vec3f(1.f, 0.0, 0.8), Vec3f(), 0.0));
    const Light light(Vec3f(-1, 2, 0), Vec3f(1.f));
    const float ambient_intensity(0.5);
    const Vec3f eye(0, 1, 0);

    Camera camera(eye, Vec3f(0, 1, 1), Vec3f(30, 4, 4), 90.f, width, height);

    //Raytracing loop
    cout << "Rendering..." << endl;

    int num_hits(0);
    int tot_rays = width * height;

    //Idea: parallelize the outer for loop
    for(int x(0); x < width; ++x) {
        for(int y(0); y < height; ++y) {
            //Trace out a primary ray for a given pixel
            Ray primary_ray(camera.primary_ray(x, y));

            //Shoot out the ray and shade the potential intersection point
            Intersection int_data(sphere.intersect(primary_ray));
            if(int_data.intersected) {
                num_hits++;
            }

            Color pixel_color = Shader::shade_point(int_data, light, ambient_intensity);

            //Write the pixel color into the final array
            (*pixels)[x][y] = pixel_color.to_color_hex();
        }
    }
    cout << (static_cast<float>(num_hits) / static_cast<float>(tot_rays)) * 100 << "% of the rays hit the sphere" << endl;
    cout << "Done rendering, writing to file..." << endl;

    //Write out the result into a bitmap
    ofstream output;  
    output.open("result.ppm", ios::out | ios::binary);

    if (output.fail()) {
        cerr << "Can't open the file" << endl;
    }

    output << "P6\n" << width << " " << height << "\n255\n"; 

    // loop over each pixel in the image and write the hex_color to the file
    for(int x(0); x < width; ++x) {
        for(int y(0); y < height; ++y) {
            output << (*pixels)[x][y];
        }
    }
    output.close(); 

    //Free the pixels array
    delete pixels;
    pixels = nullptr;

    cout << "Done!" << endl;

    return 0;
}