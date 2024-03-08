
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

    explicit Vector2(float xy = 0);

    bool operator==(const Vector2& other) const;

    bool operator!=(const Vector2& other) const;

    Vector2 operator+(const Vector2& other) const;

    Vector2 & operator+=(const Vector2& other);

    Vector2 operator-(const Vector2& other) const;

    float operator*(const Vector2& other) const;

    Vector2 operator*(const float& number) const;

    static float distance(Vector2& vector_1, Vector2& vector_2);

    Vector2 multiply(float number) const;

    Vector2 clamp() const;

    std::string to_string() const;




};

#endif
