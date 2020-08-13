#pragma once

#include <string>
#include <QColor>

using namespace std;

class Vec3f {
public:
    float x;
    float y;
    float z;

    Vec3f() = default;

    /**
     * @brief Initializes the vector with the same value in all coordinates
     * @param val, the value that will be used to initialize the vector
     */
    Vec3f(float val);

    /**
     * @brief Initializes the vector with the given coordinate values
     * @param x, the value that will be used to initialize the x coordinate
     * @param y, the value that will be used to initialize the y coordinate
     * @param z, the value that will be used to initialize the z coordinate
     */
    Vec3f(float x, float y, float z);

    /**
     * @brief Copies the given vector's values into a new vector
     * @param that, the vector that will be copied
     */
    Vec3f(Vec3f const& that);

    /**
     * @brief Returns a normalized version of the vector
     * @returns the current vector, but normalized
     */
    const Vec3f normalized() const;

    /**
     * @brief Computes the norm of the current vector
     * @returns The norm of the vector
     */
    const float length() const;

    /**
     * @brief Computes the dot product between two vectors
     * @param that, the vector with which we will compute the dot product
     * @returns the dot product between this vector and the given one
     */
    const float dot(Vec3f const& that) const;

    /**
     * @brief Computes the cross product between two vectors
     * @param that, the vector with which we will compute the cross product
     * @returns the vector produced by the cross product between this vector and the given one
     */
    const Vec3f cross(Vec3f const& that) const;

    //Operators with other vectors (component-wise operations)
    Vec3f operator+(Vec3f const& that) const;
    Vec3f operator-(Vec3f const& that) const;
    Vec3f operator*(Vec3f const& that) const;
    Vec3f operator/(Vec3f const& that) const;
    Vec3f& operator=(Vec3f const& that);
    Vec3f& operator+=(Vec3f const& that);
    Vec3f& operator-=(Vec3f const& that);
    Vec3f& operator*=(Vec3f const& that);
    Vec3f& operator/=(Vec3f const& that);

    /// reflect vector \c v at normal \c n
    const Vec3f reflected(const Vec3f& n);

    /// mirrors vector \c v at normal \c n
    const Vec3f mirrored(const Vec3f& n);

    // compute the distance between vectors \c v0 and \c v1
    const double distance_to(const Vec3f& v1);

    //Converts the vector to a hex RGB color string
    const string to_color_hex() const;

    const QRgb to_qrgb() const;

    //Computes the min between this vector and a given one
    const Vec3f min(Vec3f const& that) const;

    //Computes the max between this vector and a given one
    const Vec3f max(Vec3f const& that) const;
};
