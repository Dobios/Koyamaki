#pragma once

#include "vec3f.h"
#include "ray.h"

#include <iostream>
#include <math.h>

/// \class Camera Camera.h
/// The camera class stores the following camera parameters in its
/// member variables: eye, center, up, fovy, width, and height. The function primary_ray(x,y)
/// produces a ray from the camera center through the pixel (x,y).
class Camera
{
public:

    /// Default (empty) constructor
    Camera() {}

    /// Construct camera by specifying all required data. Calls init().
    /// \param[in] _eye Camera center
    /// \param[in] _center Center of the scene, which the camera is looking at.
    /// \param[in] _up Vector specifying the up direction.
    /// \param[in] _fovy Opening angle (field of view) in y-direction
    /// \param[in] _width Width of the image (in pixels)
    /// \param[in] _height Height of the image (in pixels)
    Camera(const Vec3f&   _eye,
           const Vec3f&   _center,
           const Vec3f&   _up,
           float          _fovy,
           unsigned int  _width,
           unsigned int  _height)
    : eye(_eye), center(_center), up(_up), fovy(_fovy), width(_width), height(_height)
    {
        init();
    }


    /// This function precomputes some variables that are later required for primary_ray()
    void init()
    {
        // compute viewing direction and distance of eye to scene center
        Vec3f  view = (center - eye).normalized();
        float dist = center.distance_to(eye);

        // compute width & height of the image plane
        // based on the opening angle of the camera (fovy) and the distance
        // of the eye to the near plane (dist)
        float w = width;
        float h = height;
        float image_height = 2.0 * dist * tan(0.5 * fovy / 180.0 * M_PI);
        float image_width  = w/h * image_height;

        // compute right and up vectors on the image plane
        x_dir = view.cross(up).normalized() * image_width / w;
        y_dir = x_dir.cross(view).normalized() * image_height / h;

        // compute lower left corner on the image plane
        lower_left = center - Vec3f(0.5f * w) * x_dir - Vec3f(0.5f * h) * y_dir;
    }


    /// create a ray for a pixel in the image
    /// \param[in] _x pixel location in image
    /// \param[in] _y pixel location in image
    Ray primary_ray(unsigned int _x, unsigned int _y) const
    {
        return Ray(eye, lower_left + Vec3f(static_cast<float>(_x)) * x_dir + Vec3f(static_cast<float>(_y)) * y_dir - eye);
    }


public:

    /// position of the eye in 3D space (camera center)
    Vec3f eye;
    
    /// the center of the scene the camera is looking at
    Vec3f center;

    /// up-direction of the camera
    Vec3f up;

    /// opening angle (field of view) in y-direction
    float fovy;

    /// image width in pixels
    unsigned int width;

    /// image height in pixels
    unsigned int height;


private:

    Vec3f x_dir;
    Vec3f y_dir;
    Vec3f lower_left;
};


//-----------------------------------------------------------------------------
