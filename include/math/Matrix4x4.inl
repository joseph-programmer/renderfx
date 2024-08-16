#ifndef MATRIX4X4_INL
#define MATRIX4X4_INL

#include <cmath>
#include <stdexcept>
#include <limits>

template<typename T>
constexpr Matrix4x4<T>::Matrix4x4() : data{ {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} } {}

template<typename T>
Matrix4x4<T>::Matrix4x4(const std::array<T, 16>& values) {
    for (int i = 0; i < 16; ++i) {
        data[i / 4][i % 4] = values[i];
    }
}

template<typename T>
T& Matrix4x4<T>::operator()(int row, int col) {
    return data[row][col];
}

template<typename T>
const T& Matrix4x4<T>::operator()(int row, int col) const {
    return data[row][col];
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& other) const {
    Matrix4x4<T> result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = 0;
            for (int k = 0; k < 4; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

template<typename T>
Vector3<T> Matrix4x4<T>::operator*(const Vector3<T>& vec) const {
    T x = vec.x * (*this)(0, 0) + vec.y * (*this)(0, 1) + vec.z * (*this)(0, 2) + (*this)(0, 3);
    T y = vec.x * (*this)(1, 0) + vec.y * (*this)(1, 1) + vec.z * (*this)(1, 2) + (*this)(1, 3);
    T z = vec.x * (*this)(2, 0) + vec.y * (*this)(2, 1) + vec.z * (*this)(2, 2) + (*this)(2, 3);
    T w = vec.x * (*this)(3, 0) + vec.y * (*this)(3, 1) + vec.z * (*this)(3, 2) + (*this)(3, 3);

    if (std::abs(w) > std::numeric_limits<T>::epsilon()) {
        x /= w; y /= w; z /= w;
    }

    return Vector3<T>(x, y, z);
}

template<typename T>
void Matrix4x4<T>::setIdentity() {
    data = { {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}} };
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::transposed() const {
    Matrix4x4<T> result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result(i, j) = (*this)(j, i);
        }
    }
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::identity() {
    return Matrix4x4<T>();
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::translation(const Vector3<T>& translation) {
    Matrix4x4<T> result;
    result.setIdentity();
    result(0, 3) = translation.x;
    result(1, 3) = translation.y;
    result(2, 3) = translation.z;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::scaling(const Vector3<T>& scale) {
    Matrix4x4<T> result;
    result.setIdentity();
    result(0, 0) = scale.x;
    result(1, 1) = scale.y;
    result(2, 2) = scale.z;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationX(T angle) {
    Matrix4x4<T> result;
    result.setIdentity();
    T c = std::cos(angle);
    T s = std::sin(angle);
    result(1, 1) = c;
    result(1, 2) = -s;
    result(2, 1) = s;
    result(2, 2) = c;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationY(T angle) {
    Matrix4x4<T> result;
    result.setIdentity();
    T c = std::cos(angle);
    T s = std::sin(angle);
    result(0, 0) = c;
    result(0, 2) = s;
    result(2, 0) = -s;
    result(2, 2) = c;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::rotationZ(T angle) {
    Matrix4x4<T> result;
    result.setIdentity();
    T c = std::cos(angle);
    T s = std::sin(angle);
    result(0, 0) = c;
    result(0, 1) = -s;
    result(1, 0) = s;
    result(1, 1) = c;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up) {
    Vector3<T> f = (center - eye).normalized();
    Vector3<T> s = f.cross(up).normalized();
    Vector3<T> u = s.cross(f);

    Matrix4x4<T> result;
    result(0, 0) = s.x;
    result(0, 1) = s.y;
    result(0, 2) = s.z;
    result(1, 0) = u.x;
    result(1, 1) = u.y;
    result(1, 2) = u.z;
    result(2, 0) = -f.x;
    result(2, 1) = -f.y;
    result(2, 2) = -f.z;
    result(0, 3) = -s.dot(eye);
    result(1, 3) = -u.dot(eye);
    result(2, 3) = f.dot(eye);
    result(3, 3) = 1;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::orthographic(T left, T right, T bottom, T top, T nearVal, T farVal) {
    Matrix4x4<T> result;
    result(0, 0) = 2 / (right - left);
    result(1, 1) = 2 / (top - bottom);
    result(2, 2) = -2 / (farVal - nearVal);
    result(0, 3) = -(right + left) / (right - left);
    result(1, 3) = -(top + bottom) / (top - bottom);
    result(2, 3) = -(farVal + nearVal) / (farVal - nearVal);
    result(3, 3) = 1;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::perspective(T fov, T aspectRatio, T near, T far) {
    Matrix4x4<T> result;
    T tanHalfFov = std::tan(fov / 2);
    result(0, 0) = 1 / (aspectRatio * tanHalfFov);
    result(1, 1) = 1 / tanHalfFov;
    result(2, 2) = -(far + near) / (far - near);
    result(2, 3) = -(2 * far * near) / (far - near);
    result(3, 2) = -1;
    result(3, 3) = 0;
    return result;
}

template<typename T>
Matrix4x4<T> Matrix4x4<T>::inverse() const {
    Matrix4x4<T> inv;
    T det;

    inv(0, 0) = data[1][1] * data[2][2] * data[3][3] -
        data[1][1] * data[2][3] * data[3][2] -
        data[2][1] * data[1][2] * data[3][3] +
        data[2][1] * data[1][3] * data[3][2] +
        data[3][1] * data[1][2] * data[2][3] -
        data[3][1] * data[1][3] * data[2][2];

    inv(1, 0) = -data[1][0] * data[2][2] * data[3][3] +
        data[1][0] * data[2][3] * data[3][2] +
        data[2][0] * data[1][2] * data[3][3] -
        data[2][0] * data[1][3] * data[3][2] -
        data[3][0] * data[1][2] * data[2][3] +
        data[3][0] * data[1][3] * data[2][2];

    inv(2, 0) = data[1][0] * data[2][1] * data[3][3] -
        data[1][0] * data[2][3] * data[3][1] -
        data[2][0] * data[1][1] * data[3][3] +
        data[2][0] * data[1][3] * data[3][1] +
        data[3][0] * data[1][1] * data[2][3] -
        data[3][0] * data[1][3] * data[2][1];

    inv(3, 0) = -data[1][0] * data[2][1] * data[3][2] +
        data[1][0] * data[2][2] * data[3][1] +
        data[2][0] * data[1][1] * data[3][2] -
        data[2][0] * data[1][2] * data[3][1] -
        data[3][0] * data[1][1] * data[2][2] +
        data[3][0] * data[1][2] * data[2][1];

    det = data[0][0] * inv(0, 0) + data[0][1] * inv(1, 0) + data[0][2] * inv(2, 0) + data[0][3] * inv(3, 0);

    if (std::abs(det) < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    det = 1.0 / det;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            inv(i, j) *= det;
        }
    }

    return inv;
}

template<typename T>
T Matrix4x4<T>::determinant() const {
    T det = data[0][0] * (data[1][1] * data[2][2] * data[3][3] + data[1][2] * data[2][3] * data[3][1] + data[1][3] * data[2][1] * data[3][2]
        - data[1][3] * data[2][2] * data[3][1] - data[1][1] * data[2][3] * data[3][2] - data[1][2] * data[2][1] * data[3][3])
        - data[0][1] * (data[1][0] * data[2][2] * data[3][3] + data[1][2] * data[2][3] * data[3][0] + data[1][3] * data[2][0] * data[3][2]
            - data[1][3] * data[2][2] * data[3][0] - data[1][0] * data[2][3] * data[3][2] - data[1][2] * data[2][0] * data[3][3])
        + data[0][2] * (data[1][0] * data[2][1] * data[3][3] + data[1][1] * data[2][3] * data[3][0] + data[1][3] * data[2][0] * data[3][1]
            - data[1][3] * data[2][1] * data[3][0] - data[1][0] * data[2][3] * data[3][1] - data[1][1] * data[2][0] * data[3][3])
        - data[0][3] * (data[1][0] * data[2][1] * data[3][2] + data[1][1] * data[2][2] * data[3][0] + data[1][2] * data[2][0] * data[3][1]
            - data[1][2] * data[2][1] * data[3][0] - data[1][0] * data[2][2] * data[3][1] - data[1][1] * data[2][0] * data[3][2]);

    return det;
}

#endif // MATRIX4X4_INL
