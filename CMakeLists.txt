cmake_minimum_required(VERSION 3.16)

project(raytracer)

file(GLOB SRCS_COMMON sphere.cpp light.cpp intersection.cpp material.cpp ray.cpp vec3f.cpp shader.cpp solver.cpp)
file(GLOB SRCS raytrace.cpp ${SRCS_COMMON})
file(GLOB HDRS ./*.h)

add_executable(raytrace raytrace.cpp ${SRCS_COMMON} ${HDRS})
