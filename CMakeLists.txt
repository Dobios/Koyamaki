cmake_minimum_required(VERSION 3.16)

project(raytracer CXX)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt5Core and Qt5Widgets
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Threads REQUIRED)

# Finding Qt includes
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

file(GLOB SRCS_COMMON src/*)
file(GLOB HDRS src/*.h)

add_executable(raytrace main.cpp ${SRCS_COMMON} ${HDRS})
target_link_libraries(raytrace Qt5::Core Qt5::Widgets)

