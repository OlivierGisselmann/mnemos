#pragma once

#include <math/vector.hpp>
#include <platform/types.hpp>

#include <cstring>
#include <iostream>

namespace Mnemos
{
    template <typename T>
    struct mat4
    {
        // Ctor
        mat4()
        {
            memset(m, static_cast<T>(0), sizeof(m));
            m[0] = m[5] = m[10] = m[15] = 1.f; // Default to identity
        }

        mat4(T diagonal)
        {
            memset(m, static_cast<T>(0), sizeof(m));
            m[0] = m[5] = m[10] = m[15] = diagonal;
        }

        mat4(const mat4<T>& mat)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(col, row) = mat(col, row);
                }
            }
        }

        ~mat4() {}

        // Value access
        inline T& operator()(int row, int col)
        {
            return m[col * 4 + row];
        }

        inline const T& operator()(int row, int col) const
        {
            return m[col * 4 + row];
        }

        // Data pointer access
        inline const f32* Data() const
        {
            return m;
        }

        inline f32* Data()
        {
            return m;
        }

        // Matrix operations
        [[nodiscard]] inline mat4<T> operator+(const mat4<T>& rhs) const
        {
            mat4<T> res;

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    res(row, col) = (*this)(row, col) + rhs(row, col);
                }
            }

            return res;
        }

        [[nodiscard]] inline mat4<T> operator-(const mat4<T>& rhs) const
        {
            mat4<T> res;

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    res(row, col) = (*this)(row, col) - rhs(row, col);
                }
            }

            return res;
        }

        [[nodiscard]] inline mat4<T> operator*(const mat4<T>& rhs) const
        {
            mat4<T> res(0.f);

            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    for(i8 k = 0; k < 4; ++k)
                    {
                        res(row, col) += (*this)(row, k) * rhs(k, col);
                    }
                }
            }

            return res;
        }

        inline mat4<T>& operator+=(const mat4<T>& rhs)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(row, col) += rhs(row, col);
                }
            }

            return (*this);
        }

        inline mat4<T>& operator-=(const mat4<T>& rhs)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    (*this)(row, col) -= rhs(row, col);
                }
            }

            return (*this);
        }

        inline mat4<T>& operator*=(const mat4<T>& rhs)
        {
            for(i8 row = 0; row < 4; ++row)
            {
                for(i8 col = 0; col < 4; ++col)
                {
                    for(i8 k = 0; k < 4; ++k)
                    {
                        (*this)(row, k) *= rhs(k, col);
                    }
                }
            }

            return (*this);
        }

    private:
        T m[16];
    };

    template <typename T>
    [[nodiscard]] inline T Radians(T degrees)
    {
        return degrees * (static_cast<T>(3.14159265) / static_cast<T>(180));
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> Translate(const mat4<T>& m, const vec3<T>& t)
    {
        mat4<T> res(m);

        res(0, 3) = t.x;
        res(1, 3) = t.y;
        res(2, 3) = t.z;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> Scale(const mat4<T>& m, const vec3<T>& s)
    {
        mat4<T> res(m);

        res(0, 0) = s.x;
        res(1, 1) = s.y;
        res(2, 2) = s.z;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> Rotate(const mat4<T>& m, T angle, const vec3<T>& v)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

		vec3<T> axis = Normalize(v);

        mat4<T> res(m);

		res(0, 0) = c + (static_cast<T>(1) - c)      * axis.x     * axis.x;
		res(0, 1) = (static_cast<T>(1) - c) * axis.x * axis.y + s * axis.z;
		res(0, 2) = (static_cast<T>(1) - c) * axis.x * axis.z - s * axis.y;
		res(0, 3) = static_cast<T>(0);

		res(1, 0) = (static_cast<T>(1) - c) * axis.y * axis.x - s * axis.z;
		res(1, 1) = c + (static_cast<T>(1) - c) * axis.y * axis.y;
		res(1, 2) = (static_cast<T>(1) - c) * axis.y * axis.z + s * axis.x;
		res(1, 3) = static_cast<T>(0);

		res(2, 0) = (static_cast<T>(1) - c) * axis.z * axis.x + s * axis.y;
		res(2, 1) = (static_cast<T>(1) - c) * axis.z * axis.y - s * axis.x;
		res(2, 2) = c + (static_cast<T>(1) - c) * axis.z * axis.z;
		res(2, 3) = static_cast<T>(0);

		res(3, 0) = 0;
		res(3, 1) = 0;
		res(3, 2) = 0;
		res(3, 3) = 1;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> RotateX(const mat4<T>& m, T angle)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

        mat4<T> res;

        res(1, 1) = c;
        res(1, 2) = -s;
        res(2, 1) = s;
        res(2, 2) = c;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> RotateY(const mat4<T>& m, T angle)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

        mat4<T> res;

        res(0, 0) = c;
        res(0, 2) = s;
        res(2, 0) = -s;
        res(2, 2) = c;

        return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> RotateZ(const mat4<T>& m, T angle)
    {
        const T a = Radians(angle);
        const T c = std::cos(a);
        const T s = std::sin(a);

        mat4<T> res;

        res(0, 0) = c;
        res(0, 1) = -s;
        res(1, 0) = s;
        res(1, 1) = c;
        
        return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> Perspective(T fov, T aspect, T near, T far)
    {
        const T range = std::tan(Radians(fov) / static_cast<T>(2));

		mat4<T> res(0.f);

		res(0, 0) = static_cast<T>(1) / (aspect * range);
		res(1, 1) = static_cast<T>(1) / (range);
		res(2, 2) = - (far + near) / (far - near);
		res(2, 3) = - (static_cast<T>(2) * far * near) / (far - near);
		res(3, 2) = - static_cast<T>(1);

		return res;
    }

    template <typename T>
    [[nodiscard]] inline mat4<T> LookAt(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up)
    {
        mat4<T> res;

        vec3<T> f = Normalize(eye - center);
        vec3<T> s = Normalize(Cross(Normalize(up), f));
        vec3<T> u = Normalize(Cross(f, s));

        vec3<T> t(0.f);
        t.x = Dot(s, eye);
        t.y = Dot(u, eye);
        t.z = Dot(f, eye);

        res(0, 0) = s.x;
        res(0, 1) = s.y;
        res(0, 2) = s.z;

        res(1, 0) = u.x;
        res(1, 1) = u.y;
        res(1, 2) = u.z;

        res(2, 0) = f.x;
        res(2, 1) = f.y;
        res(2, 2) = f.z;

        res(0, 3) = t.x;
        res(1, 3) = t.y;
        res(2, 3) = t.z;

        return res;
    }
}
