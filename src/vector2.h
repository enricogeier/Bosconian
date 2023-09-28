
#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>

class Vector2
{
public:

    float x;
    float y;

    explicit Vector2(float x = 0.0f, float y = 0.0f)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Vector2& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Vector2& other) const
    {
        return (x != other.x) || (y != other.y);
    }

    std::string to_string() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

};

#endif
