//
// Created by brand on 8/08/2026.
//

#ifndef HI_VEC2_H
#define HI_VEC2_H

#include <cmath>

class Vec2 {
public:
    float x, y;

    Vec2()
        : x(0), y(0)
    {
    }

    Vec2(float givenx, float giveny)
        : x(givenx), y(giveny)
    {
    }

    Vec2 operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(float value) const
    {
        return Vec2(x * value, y * value);
    }

    Vec2 operator/(float value) const
    {
        return Vec2(x / value, y / value);
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    float LengthSquared() const
    {
        return x * x + y * y;
    }

    Vec2 Normalized() const
    {
        float length = Length();

        if(length == 0)
        {
            return Vec2(0, 0);
        }

        return Vec2(x / length, y / length);
    }

    float Dot(const Vec2& other) const
    {
        return x * other.x + y * other.y;
    }
};

#endif //HI_VEC2_H