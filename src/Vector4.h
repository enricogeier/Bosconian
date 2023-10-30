#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>
#include <cmath>

class Vector4
{
public:

    float x;
    float y;
    float z;
    float w;

    explicit Vector4(float x, float y, float z, float w);

    explicit Vector4(float xyzw = 0.0f);

    bool operator==(const Vector4& other) const;

    bool operator!=(const Vector4& other) const;

    Vector4 operator+(Vector4& other) const;

    Vector4 operator-(Vector4& other) const;

    float operator*(Vector4& other) const;

    Vector4 multiply(float number) const;

    std::string to_string() const;

};



#endif
