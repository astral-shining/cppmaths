#pragma once
#include <cpputils/types.hpp>
#include <cpputils/string.hpp>

#define VecOP(S, v1, v2, r) \
for (u32 i{}; i<N; i++) { \
    r.data[i] = v1.data[i] S v2.data[i]; \
}

template<u32 N, typename T = float>
struct VecBase {
    T data[N];

    template<typename... Ts>
    requires (sizeof...(Ts) == N)
    constexpr VecBase(Ts... v) : data{v...} {

    }

    constexpr VecBase(const VecBase& v) {
        *this = v;
    }

    constexpr VecBase& operator=(const VecBase& v) {
        for (u32 i{}; i<N; i++) {
            data[i] = v.data[i];
        }
        return *this;
    }

    constexpr VecBase operator+(const VecBase& v) {
        VecBase result;
        VecOP(+, (*this), v, result)
        return result;
    }

    constexpr VecBase& operator+=(const VecBase& v) {
        VecOP(+, (*this), v, (*this))
        return *this;
    }

    constexpr VecBase operator-(const VecBase& v) {
        VecBase result;
        VecOP(-, (*this), v, result)
        return result;
    }

    constexpr VecBase& operator-=(const VecBase& v) {
        VecOP(-, (*this), v, (*this))
        return *this;
    }

    constexpr VecBase operator*(const VecBase& v) {
        VecBase result;
        VecOP(*, (*this), v, result)
        return result;
    }

    constexpr VecBase& operator*=(const VecBase& v) {
        VecOP(*, (*this), v, (*this))
        return *this;
    }

    constexpr VecBase operator/(const VecBase& v) {
        VecBase result;
        VecOP(/, (*this), v, result)
        return result;
    }

    constexpr VecBase& operator/=(const VecBase& v) {
        VecOP(/, (*this), v, (*this))
        return *this;
    }

    String toString() {
        String s {""};
        for (u32 i{}; i<N; i++) {
            s += data[i] + "f ";
        }
        return s;
    }
};

template<u32 N, typename T>
struct Vec {};

template<typename T>
struct Vec<2, T> : VecBase<2, T> {
    constexpr Vec(T x, T y) : VecBase<2, T>(x, y) {}
    T& x = VecBase<2, T>::data[0];
    T& y = VecBase<2, T>::data[1];
};

template<typename T>
struct Vec<3, T> : VecBase<3, T> {
    constexpr Vec(T x, T y, T z) : VecBase<3, T>(x, y, z) {}
    T& x = VecBase<3, T>::data[0];
    T& y = VecBase<3, T>::data[1];
    T& z = VecBase<3, T>::data[2];
};

template<typename T>
struct Vec<4, T> : VecBase<4, T> {
    constexpr Vec(T x, T y, T z, T w) : VecBase<4, T>(x, y, z, w) {}
    T& x = VecBase<4, T>::data[0];
    T& y = VecBase<4, T>::data[1];
    T& z = VecBase<4, T>::data[2];
    T& w = VecBase<4, T>::data[3];
};

using Vec2 = Vec<2, float>;
using Vec3 = Vec<3, float>;
using Vec4 = Vec<4, float>;

using iVec2 = Vec<2, i32>;
using iVec3 = Vec<3, i32>;
using iVec4 = Vec<4, i32>;

using uVec2 = Vec<2, u32>;
using uVec3 = Vec<3, u32>;
using uVec4 = Vec<4, u32>;
