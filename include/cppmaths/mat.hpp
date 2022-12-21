#pragma once
#include <cpputils/types.hpp>

extern "C" double cos(double);
extern "C" double sin(double);

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
            data[i][i] = value;
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

    void rotate(float deg) requires (rows == 3 && columns == 3) {
        auto c = cos(deg);
        auto s = sin(deg);

        data[0][0] = c; data[0][1] = -s; 
        data[1][0] = s; data[1][1] = c; 
    }
};

using Mat4 = Mat<4, 4, float>;
using Mat3 = Mat<3, 3, float>;
