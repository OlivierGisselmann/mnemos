#pragma once

#include <platform/types.hpp>

#include <cmath>

namespace Mnemos
{
    template <typename T>
    struct vec3
    {
        T x, y, z;

        // Ctor
        vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        vec3(T value) : x(value), y(value), z(value) {}
        vec3(const vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {}
        ~vec3() = default;

        // Vector operations
        [[nodiscard]] inline vec3<T> operator+(const vec3<T>& v) const
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        [[nodiscard]] inline vec3<T> operator-(const vec3<T>& v) const
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        [[nodiscard]] inline vec3<T> operator/(const vec3<T>& v) const
        {
            return {x / v.x, y / v.y, z / v.z};
        }

        inline vec3<T>& operator+=(const vec3<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        inline vec3<T>& operator-=(const vec3<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        inline vec3<T>& operator/=(const vec3<T>& v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }

        // Scalar operations
        [[nodiscard]] inline vec3<T> operator+(T value) const
        {
            return {x + value, y + value, z + value};
        }

        [[nodiscard]] inline vec3<T> operator-(T value) const
        {
            return {x - value, y - value, z - value};
        }

        [[nodiscard]] inline vec3<T> operator*(T value) const
        {
            return {x * value, y * value, z *value};
        }

        [[nodiscard]] inline vec3<T> operator/(T value) const
        {
            return {x / value, y / value, z / value};
        }
    };

    template <typename T>
    [[nodiscard]] inline T Length(const vec3<T>& v)
    {
        return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }

    template <typename T>
    [[nodiscard]] inline vec3<T> Normalize(const vec3<T>& v)
    {
        return v / Length(v);
    }

    template <typename T>
    [[nodiscard]] inline T Dot(const vec3<T>& v1, const vec3<T>& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }

    template <typename T>
    [[nodiscard]] inline vec3<T> Cross(const vec3<T>& v1, const vec3<T>& v2)
    {
        return
        {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }
}
