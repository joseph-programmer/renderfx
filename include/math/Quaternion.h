#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdexcept>
#include "Vector3.h"
#include "Matrix4x4.h"

/**
 * @brief A quaternion class template.
 * 
 * This class represents a quaternion and provides various operations for quaternion mathematics.
 * 
 * @tparam T Type of the elements in the quaternion.
 */
template<typename T>
class Quaternion {
public:
    T w, x, y, z; ///< Quaternion components.

    /**
     * @brief Default constructor. Initializes the quaternion with (1, 0, 0, 0).
     */
    constexpr Quaternion();

    /**
     * @brief Constructor with specified components.
     * 
     * @param w The real part of the quaternion.
     * @param x The i component of the quaternion.
     * @param y The j component of the quaternion.
     * @param z The k component of the quaternion.
     */
    constexpr Quaternion(T w, T x, T y, T z);

    /**
     * @brief Constructor from axis-angle representation.
     * 
     * @param axis The axis of rotation.
     * @param angle The angle of rotation in radians.
     */
    Quaternion(const Vector3<T>& axis, T angle);

    /**
     * @brief Multiplies this quaternion by another quaternion.
     * 
     * @param q The quaternion to multiply by.
     * @return The result of the quaternion multiplication.
     */
    constexpr Quaternion operator*(const Quaternion& q) const;

    /**
     * @brief Rotates a vector by this quaternion.
     * 
     * @param v The vector to rotate.
     * @return The rotated vector.
     */
    Vector3<T> operator*(const Vector3<T>& v) const;

    /**
     * @brief Calculates the magnitude (norm) of the quaternion.
     * 
     * @return The magnitude of the quaternion.
     */
    T magnitude() const;

    /**
     * @brief Returns the normalized quaternion.
     * 
     * @return The normalized quaternion.
     */
    Quaternion normalized() const;

    /**
     * @brief Returns the conjugate of the quaternion.
     * 
     * @return The conjugate of the quaternion.
     */
    Quaternion conjugate() const;

    /**
     * @brief Returns the inverse of the quaternion.
     * 
     * @return The inverse of the quaternion.
     */
    Quaternion inverse() const;

    /**
     * @brief Converts the quaternion to a rotation matrix.
     * 
     * @return The rotation matrix corresponding to this quaternion.
     */
    Matrix4x4<T> toRotationMatrix() const;

    /**
     * @brief Converts the quaternion to Euler angles.
     * 
     * @return A vector containing the Euler angles (pitch, yaw, roll).
     */
    Vector3<T> toEulerAngles() const;

    /**
     * @brief Creates a quaternion from an axis-angle representation.
     * 
     * @param axis The axis of rotation.
     * @param angle The angle of rotation in radians.
     * @return The resulting quaternion.
     */
    static Quaternion fromAxisAngle(const Vector3<T>& axis, T angle);

    /**
     * @brief Creates a quaternion from Euler angles.
     * 
     * @param pitch The pitch angle in radians.
     * @param yaw The yaw angle in radians.
     * @param roll The roll angle in radians.
     * @return The resulting quaternion.
     */
    static Quaternion fromEulerAngles(T pitch, T yaw, T roll);

    /**
     * @brief Spherical linear interpolation between two quaternions.
     * 
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation parameter, between 0 and 1.
     * @return The interpolated quaternion.
     */
    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, T t);
};

// Commonly used types
using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;

#include "Quaternion.inl"

#endif // QUATERNION_H
