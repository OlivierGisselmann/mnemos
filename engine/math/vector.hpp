#pragma once

#include <platform/types.hpp>

#include <cmath>

namespace Mnemos
{
    // Vector 2
    template <typename T>
    struct vec2
    {
        T x, y;

        vec2(T _x, T _y) : x(_x), y(_y) {}
        vec2(const vec2<T>& v) : x(v.x), y(v.y) {}

        inline vec2<T> operator+(const vec2<T>& v)
        {
            return {x + v.x, y + v.y};
        }

        inline vec2<T> operator-(const vec2<T>& v)
        {
            return {x - v.x, y - v.y};
        }

        inline f32 length()
        {
            return std::sqrt((x*x) + (y*y));
        }
    };

    typedef vec2<i32> vec2i;
    typedef vec2<f32> vec2f;

    template <typename T>
    inline f32 dot(const vec2<T>& v1, const vec2<T>& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    // Vector3
    template <typename T>
    struct vec3
    {
        T x, y, z;

        vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        vec3(const vec3<T>& v) : x(v.x), y(v.y), z(v.z) {}

        inline vec3<T> operator+(const vec3<T>& v)
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        inline vec3<T> operator-(const vec3<T>& v)
        {
            return {x - v.x, y - v.y, z - v.z};
        }

        inline f32 length()
        {
            return std::sqrt((x*x) + (y*y) + (z*z));
        }
    };

    template <typename T>
    inline f32 dot(const vec3<T>& v1, const vec3<T>& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    }

    template <typename T>
    inline vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2)
    {
        return
        {
            (v1.y * v2.z) - (v1.z * v2.y),
            (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)
        };
    }

    typedef vec3<i32> vec3i;
    typedef vec3<f32> vec3f;
}
