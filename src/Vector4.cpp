#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

Vector4::Vector4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw)
{
}

bool Vector4::operator==(const Vector4 &other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(const Vector4 &other) const
{
    return !(x == other.x && y == other.y && z == other.z && w == other.w);
}

Vector4 Vector4::operator+(Vector4 &other) const
{
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4 Vector4::operator-(Vector4 &other) const
{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

float Vector4::operator*(Vector4 &other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Vector4::multiply(float number) const
{
    return Vector4(x * number, y * number, z * number, w * number);
}

std::string Vector4::to_string() const
{
   return "(" + std::to_string(this->x) + ", " + std::to_string(this->y)  + ", " + std::to_string(this->z)  + ", " + std::to_string(this->w) + ")";
}