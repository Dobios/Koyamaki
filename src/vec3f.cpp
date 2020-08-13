#include "vec3f.h"

#include <limits>
#include <math.h>
#include <iomanip>


using namespace std;

//Constructors and copy constructor
Vec3f::Vec3f(float val) : x(val), y(val), z(val) {}
Vec3f::Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}
Vec3f::Vec3f(Vec3f const& that) : x(that.x), y(that.y), z(that.z) {}

const float Vec3f::length() const {
    return sqrt(this->dot(*this));
}

const Vec3f Vec3f::normalized() const {
    return (*this) / Vec3f(this->length());
}

const float Vec3f::dot(Vec3f const& that) const {
    return (this->x * that.x) + (this->y * that.y) + (this->z * that.z); 
}

const Vec3f Vec3f::cross(Vec3f const& that) const {
    return Vec3f(
        (this->y * that.z) - (this->z * that.y),
        (this->z * that.x) - (this->x * that.z),
        (this->x * that.y) - (this->y * that.x) 
    );
}

const Vec3f Vec3f::reflected(const Vec3f& n) {
    return (*this) - Vec3f(2.0 * n.dot(*this)) * n;
}

const Vec3f Vec3f::mirrored(const Vec3f& n)
{
    return Vec3f(2.0 * n.dot(*this)) * n - (*this);
}

const double Vec3f::distance_to(const Vec3f& v1)
{
    return ((*this) - v1).length();
}

const Vec3f Vec3f::min(Vec3f const& that) const {
    return Vec3f(
        std::min(this->x, that.x),
        std::min(this->y, that.y), 
        std::min(this->z, that.z)
    );
}

const Vec3f Vec3f::max(Vec3f const& that) const {
    return Vec3f(
        std::max(this->x, that.x),
        std::max(this->y, that.y), 
        std::max(this->z, that.z)
    );
}

const QRgb Vec3f::to_qrgb() const {
    Vec3f color_vec(this->min(Vec3f(1.f)).max(Vec3f(0.f)));

    //Extract the rgb components
    uint8_t r(color_vec.x * 255);
    uint8_t g(color_vec.y * 255);
    uint8_t b(color_vec.z * 255);

    return (0xFF) << 24 | r << 16 | g << 8 | b;
}

const string Vec3f::to_color_hex() const {
    //Clamp the components to [0 , 1]
    Vec3f color_vec(this->min(Vec3f(1.f)).max(Vec3f(0.f)));

    //Extract the rgb components 
    uint8_t r(color_vec.x * 255);
    uint8_t g(color_vec.y * 255);
    uint8_t b(color_vec.z * 255);

    //Convert the colors to hex strings
    stringstream stream_r;
    stream_r << hex << r;
    string r_res( stream_r.str() );

    stringstream stream_g;
    stream_g << hex << g;
    string g_res( stream_g.str() );

    stringstream stream_b;
    stream_b << hex << b;
    string b_res( stream_b.str() );

    stringstream stream_res;

    //Write out the final hex string
    stream_res << r_res << g_res << b_res;

    return stream_res.str();
}

Vec3f& Vec3f::operator=(Vec3f const& that) {
    this->x = that.x;
    this->y = that.y;
    this->z = that.z;

    return (*this);
}

Vec3f Vec3f::operator+(Vec3f const& that) const {
    return Vec3f(this->x + that.x, this->y + that.y, this->z + that.z);
}

Vec3f& Vec3f::operator+=(Vec3f const& that) {
    this->x += that.x;
    this->y += that.y;
    this->z += that.z;

    return (*this);
}

Vec3f Vec3f::operator-(Vec3f const& that) const {
    return Vec3f(this->x - that.x, this->y - that.y, this->z - that.z);
}

Vec3f& Vec3f::operator-=(Vec3f const& that) {
    this->x -= that.x;
    this->y -= that.y;
    this->z -= that.z;

    return (*this);
}

Vec3f Vec3f::operator*(Vec3f const& that) const {
    return Vec3f(this->x * that.x, this->y * that.y, this->z * that.z);
}

Vec3f& Vec3f::operator*=(Vec3f const& that) {
    this->x *= that.x;
    this->y *= that.y;
    this->z *= that.z;

    return (*this);
}

Vec3f Vec3f::operator/(Vec3f const& that) const {
    //Sanity check
    float new_x(0.f);
    float new_y(0.f);
    float new_z(0.f);

    if(that.x == 0) {
        new_x = std::numeric_limits<float>::max();
    } else {
        new_x = this->x / that.x;
    }

    if(that.y == 0) {
        new_y = std::numeric_limits<float>::max();
    } else {
        new_y = this->y / that.y;
    }

    if(that.z == 0) {
        new_z = std::numeric_limits<float>::max();
    } else {
        new_z = this->z / that.z;
    }

    return Vec3f(new_x, new_y, new_z);
}

Vec3f& Vec3f::operator/=(Vec3f const& that) {
    return (*this) = (*this) / that;
}
