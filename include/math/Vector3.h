#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>

/**
 * @class Vector3
 * @brief A template class for a 3D vector.
 *
 * This class represents a three-dimensional vector and provides various
 * vector operations such as addition, subtraction, scalar multiplication,
 * dot product, cross product, and more.
 */
template<typename T>
class Vector3 {
public:
    T x, y, z; ///< The x, y, and z components of the vector.

    /// @name Constructors
    /// @{
    
    /**
     * @brief Default constructor.
     * Initializes all components to zero.
     */
    constexpr Vector3();

    /**
     * @brief Parameterized constructor.
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     */
    constexpr Vector3(T x, T y, T z);
    
    /// @}

    /// @name Copy and Move Operations
    /// @{

    /**
     * @brief Default copy constructor.
     */
    Vector3(const Vector3&) = default;

    /**
     * @brief Default copy assignment operator.
     */
    Vector3& operator=(const Vector3&) = default;

    /**
     * @brief Default move constructor.
     */
    Vector3(Vector3&&) = default;

    /**
     * @brief Default move assignment operator.
     */
    Vector3& operator=(Vector3&&) = default;

    /// @}

    /// @name Array Subscript Operator
    /// @{
    
    /**
     * @brief Accesses a component of the vector.
     * @param i Index (0 for x, 1 for y, 2 for z).
     * @return Reference to the component.
     */
    T& operator[](int i);

    /**
     * @brief Accesses a component of the vector (const version).
     * @param i Index (0 for x, 1 for y, 2 for z).
     * @return Const reference to the component.
     */
    const T& operator[](int i) const;

    /// @}

    /// @name Vector Addition and Subtraction
    /// @{
    
    /**
     * @brief Adds two vectors.
     * @param v The vector to add.
     * @return The resulting vector.
     */
    Vector3 operator+(const Vector3& v) const;

    /**
     * @brief Subtracts a vector from this vector.
     * @param v The vector to subtract.
     * @return The resulting vector.
     */
    Vector3 operator-(const Vector3& v) const;

    /**
     * @brief Adds a vector to this vector.
     * @param v The vector to add.
     * @return Reference to this vector.
     */
    Vector3& operator+=(const Vector3& v);

    /**
     * @brief Subtracts a vector from this vector.
     * @param v The vector to subtract.
     * @return Reference to this vector.
     */
    Vector3& operator-=(const Vector3& v);

    /// @}

    /// @name Scalar Multiplication and Division
    /// @{
    
    /**
     * @brief Multiplies the vector by a scalar.
     * @param s The scalar value.
     * @return The resulting vector.
     */
    Vector3 operator*(T s) const;

    /**
     * @brief Divides the vector by a scalar.
     * @param s The scalar value.
     * @return The resulting vector.
     */
    Vector3 operator/(T s) const;

    /**
     * @brief Multiplies this vector by a scalar.
     * @param s The scalar value.
     * @return Reference to this vector.
     */
    Vector3& operator*=(T s);

    /**
     * @brief Divides this vector by a scalar.
     * @param s The scalar value.
     * @return Reference to this vector.
     */
    Vector3& operator/=(T s);

    /**
     * @brief Multiplies two vectors component-wise.
     * @param other The vector to multiply with.
     * @return The resulting vector.
     */
    Vector3 operator*(const Vector3& other) const;

    /// @}

    /// @name Dot Product
    /// @{
    
    /**
     * @brief Computes the dot product with another vector.
     * @param v The other vector.
     * @return The dot product.
     */
    T dot(const Vector3& v) const;

    /// @}

    /// @name Cross Product
    /// @{
    
    /**
     * @brief Computes the cross product with another vector.
     * @param v The other vector.
     * @return The resulting vector.
     */
    Vector3 cross(const Vector3& v) const;

    /// @}

    /// @name Length Calculations
    /// @{
    
    /**
     * @brief Computes the squared length of the vector.
     * @return The squared length.
     */
    T lengthSquared() const;

    /**
     * @brief Computes the length of the vector.
     * @return The length.
     */
    T length() const;

    /// @}

    /// @name Normalization
    /// @{
    
    /**
     * @brief Returns a normalized copy of the vector.
     * @return The normalized vector.
     */
    Vector3 normalized() const;

    /**
     * @brief Normalizes the vector in place.
     */
    void normalize();

    /// @}

    /// @name Comparison Operators
    /// @{
    
    /**
     * @brief Checks if two vectors are equal.
     * @param v The vector to compare with.
     * @return True if equal, false otherwise.
     */
    bool operator==(const Vector3& v) const;

    /**
     * @brief Checks if two vectors are not equal.
     * @param v The vector to compare with.
     * @return True if not equal, false otherwise.
     */
    bool operator!=(const Vector3& v) const;

    /// @}

    /// @name Advanced Features
    /// @{
    
    /**
     * @brief Projects this vector onto another vector.
     * @param v The vector to project onto.
     * @return The projected vector.
     */
    Vector3 projectOnto(const Vector3& v) const;

    /**
     * @brief Reflects this vector across a normal vector.
     * @param normal The normal vector to reflect across.
     * @return The reflected vector.
     */
    Vector3 reflect(const Vector3& normal) const;

    /**
     * @brief Linearly interpolates between two vectors.
     * @param a The start vector.
     * @param b The end vector.
     * @param t The interpolation factor [0, 1].
     * @return The interpolated vector.
     */
    static Vector3 lerp(const Vector3& a, const Vector3& b, T t);

    /**
     * @brief Spherically interpolates between two vectors.
     * @param a The start vector.
     * @param b The end vector.
     * @param t The interpolation factor [0, 1].
     * @return The interpolated vector.
     */
    static Vector3 slerp(const Vector3& a, const Vector3& b, T t);

    /// @}

    /// @name Utility Functions
    /// @{
    
    /**
     * @brief Returns a vector with all components set to zero.
     * @return The zero vector.
     */
    static constexpr Vector3 zero();

    /**
     * @brief Returns a vector with all components set to one.
     * @return The one vector.
     */
    static constexpr Vector3 one();

    /**
     * @brief Returns a unit vector pointing up.
     * @return The up vector.
     */
    static constexpr Vector3 up();

    /**
     * @brief Returns a unit vector pointing down.
     * @return The down vector.
     */
    static constexpr Vector3 down();

    /**
     * @brief Returns a unit vector pointing left.
     * @return The left vector.
     */
    static constexpr Vector3 left();

    /**
     * @brief Returns a unit vector pointing right.
     * @return The right vector.
     */
    static constexpr Vector3 right();

    /**
     * @brief Returns a unit vector pointing forward.
     * @return The forward vector.
     */
    static constexpr Vector3 forward();

    /**
     * @brief Returns a unit vector pointing backward.
     * @return The backward vector.
     */
    static constexpr Vector3 backward();

    /// @}

    /// @name Stream Output
    /// @{
    
    /**
     * @brief Overload of the stream insertion operator for Vector3.
     * @param os The output stream.
     * @param v The vector to output.
     * @return The output stream.
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector3<U>& v);

    /// @}
};

// Scalar multiplication (scalar * vector)
template<typename T>
Vector3<T> operator*(T s, const Vector3<T>& v);

// Commonly used types
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3i = Vector3<int>;

#include "Vector3.inl"

#endif // VECTOR3_H
