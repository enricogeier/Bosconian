
#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include <cmath>

class Vector2
{
public:

    float x;
    float y;

    explicit Vector2(float x, float y);

    explicit Vector2(float xy = 0.0f);

    bool operator==(const Vector2& other) const;

    bool operator!=(const Vector2& other) const;

    Vector2 operator+(Vector2& other) const;

    Vector2 operator-(Vector2& other) const;

    float operator*(Vector2& other) const;

    Vector2 multiply(float number) const;

    Vector2 clamp() const;

    std::string to_string() const;

};

#endif
