#pragma once
#include <cpputils/types.hpp>

template<u32 rows, u32 columns, typename T = float>
struct Mat {
    T data[rows][columns];

    Mat(const Mat& other) {
        *this = other;
    }

    Mat(T value = 1.f) {
        *this = value;
    }

    Mat& operator=(const Mat& other) {
        for (u32 i = 0; i < rows; i++) {
            for (u32 j = 0; j < columns; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }

    Mat& operator=(T value) {
        for (u32 i = 0; i < rows; i++) {
            for (u32 j = 0; j < columns; j++) {
                data[i][j] = value;
            }
        }
        return *this;
    }

    template<u32 columns_m2>
    Mat operator*(const Mat<columns, columns_m2>& other) {
        Mat<rows, columns_m2> result;
        for (u32 i = 0; i < rows; i++) {
            for (u32 j = 0; j < columns_m2; j++) {
                result.data[i][j] = 0;
                for (u32 k = 0; k < columns; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    template<u32 columns_m2>
    Mat& operator*=(const Mat<columns, columns_m2>& other) {
        auto mat = (*this)*other;
        (*this) = mat;
        return *this;
    }
};

using Mat4 = Mat<4, 4, float>;
using Mat3 = Mat<3, 3, float>;
