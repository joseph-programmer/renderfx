#ifndef QUATERNION_INL
#define QUATERNION_INL

#define _USE_MATH_DEFINES
#include <math.h>
#include <limits>

template<typename T>
constexpr Quaternion<T>::Quaternion() : w(1), x(0), y(0), z(0) {}

template<typename T>
constexpr Quaternion<T>::Quaternion(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

template<typename T>
Quaternion<T>::Quaternion(const Vector3<T>& axis, T angle) {
    T halfAngle = angle * T(0.5);
    T sinHalfAngle = std::sin(halfAngle);
    w = std::cos(halfAngle);
    x = axis.x * sinHalfAngle;
    y = axis.y * sinHalfAngle;
    z = axis.z * sinHalfAngle;
}

template<typename T>
constexpr Quaternion<T> Quaternion<T>::operator*(const Quaternion& q) const {
    return Quaternion(
        w * q.w - x * q.x - y * q.y - z * q.z,
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w
    );
}

template<typename T>
Vector3<T> Quaternion<T>::operator*(const Vector3<T>& v) const {
    Quaternion p(0, v.x, v.y, v.z);
    Quaternion q = (*this) * p * conjugate();
    return Vector3<T>(q.x, q.y, q.z);
}

template<typename T>
T Quaternion<T>::magnitude() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

template<typename T>
Quaternion<T> Quaternion<T>::normalized() const {
    T mag = magnitude();
    if (mag < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Cannot normalize zero quaternion");
    }
    return Quaternion(w / mag, x / mag, y / mag, z / mag);
}

template<typename T>
Quaternion<T> Quaternion<T>::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

template<typename T>
Quaternion<T> Quaternion<T>::inverse() const {
    T magSquared = w * w + x * x + y * y + z * z;
    if (magSquared < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Cannot invert zero quaternion");
    }
    T invMagSquared = T(1) / magSquared;
    return Quaternion(w * invMagSquared, -x * invMagSquared, -y * invMagSquared, -z * invMagSquared);
}

template<typename T>
Matrix4x4<T> Quaternion<T>::toRotationMatrix() const {
    T xx = x * x, yy = y * y, zz = z * z;
    T xy = x * y, xz = x * z, yz = y * z;
    T wx = w * x, wy = w * y, wz = w * z;

    Matrix4x4<T> m;
    m(0, 0) = 1 - 2 * (yy + zz);
    m(0, 1) = 2 * (xy - wz);
    m(0, 2) = 2 * (xz + wy);
    m(1, 0) = 2 * (xy + wz);
    m(1, 1) = 1 - 2 * (xx + zz);
    m(1, 2) = 2 * (yz - wx);
    m(2, 0) = 2 * (xz - wy);
    m(2, 1) = 2 * (yz + wx);
    m(2, 2) = 1 - 2 * (xx + yy);
    m(3, 3) = 1;

    return m;
}

template<typename T>
Vector3<T> Quaternion<T>::toEulerAngles() const {
    Vector3<T> angles;

    // Roll (x-axis rotation)
    T sinr_cosp = 2 * (w * x + y * z);
    T cosr_cosp = 1 - 2 * (x * x + y * y);
    angles.x = std::atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    T sinp = 2 * (w * y - z * x);
    if (std::abs(sinp) >= 1)
        angles.y = std::copysign(M_PI / 2, sinp); // Use 90 degrees if out of range
    else
        angles.y = std::asin(sinp);

    // Yaw (z-axis rotation)
    T siny_cosp = 2 * (w * z + x * y);
    T cosy_cosp = 1 - 2 * (y * y + z * z);
    angles.z = std::atan2(siny_cosp, cosy_cosp);

    return angles;
}

template<typename T>
Quaternion<T> Quaternion<T>::fromAxisAngle(const Vector3<T>& axis, T angle) {
    T halfAngle = angle * static_cast<T>(0.5);
    T sinHalfAngle = std::sin(halfAngle);
    return Quaternion(std::cos(halfAngle), axis.x * sinHalfAngle, axis.y * sinHalfAngle, axis.z * sinHalfAngle);
}

template<typename T>
Quaternion<T> Quaternion<T>::fromEulerAngles(T pitch, T yaw, T roll) {
    T cy = std::cos(yaw * 0.5);
    T sy = std::sin(yaw * 0.5);
    T cp = std::cos(pitch * 0.5);
    T sp = std::sin(pitch * 0.5);
    T cr = std::cos(roll * 0.5);
    T sr = std::sin(roll * 0.5);

    return Quaternion(
        cr * cp * cy + sr * sp * sy,
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy
    );
}

template<typename T>
Quaternion<T> Quaternion<T>::slerp(const Quaternion& q1, const Quaternion& q2, T t) {
    Quaternion q2_adj = q2;
    T dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

    if (dot < 0) {
        q2_adj = Quaternion(-q2.w, -q2.x, -q2.y, -q2.z);
        dot = -dot;
    }

    if (dot > 0.9995) {
        return Quaternion(
            q1.w + t * (q2_adj.w - q1.w),
            q1.x + t * (q2_adj.x - q1.x),
            q1.y + t * (q2_adj.y - q1.y),
            q1.z + t * (q2_adj.z - q1.z)
        ).normalized();
    }

    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;
    T sin_theta = std::sin(theta);
    T sin_theta_0 = std::sin(theta_0);

    T s0 = std::cos(theta) - dot * sin_theta / sin_theta_0;
    T s1 = sin_theta / sin_theta_0;

    return Quaternion(
        s0 * q1.w + s1 * q2_adj.w,
        s0 * q1.x + s1 * q2_adj.x,
        s0 * q1.y + s1 * q2_adj.y,
        s0 * q1.z + s1 * q2_adj.z
    );
}

#endif // QUATERNION_INL
