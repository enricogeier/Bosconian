#include "Vector2.h"

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(float xy) : x(xy), y(xy)
{

}

bool Vector2::operator==(const Vector2& other) const
{
    return (this->x == other.x) && (this->y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
    return (this->x != other.x) || (this->y != other.y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(this->x +  other.x, this->y + other.y);
}

Vector2 & Vector2::operator+=(const Vector2 &other)
{
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(this->x - other.x, this->y - other.y);
}

float Vector2::operator*(const Vector2& other) const
{
    return (this->x * other.x) + (this->y * other.y);
}

Vector2 Vector2::operator*(const float &number) const
{
    return Vector2(this->x * number, this->y * number);
}

float Vector2::distance(Vector2 &vector_1, Vector2 &vector_2)
{
    Vector2 sub = vector_1 - vector_2;
    return sqrtf(powf(sub.x, 2) + powf(sub.y, 2));
}

Vector2 Vector2::multiply(float number) const
{
    return Vector2(this->x * number, this->y * number);
}

Vector2 Vector2::clamp() const
{
    float length = sqrtf(powf(this->x, 2) + powf(this->y, 2));

    return multiply(1 / length);

}

std::string Vector2::to_string() const
{
    return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
}
