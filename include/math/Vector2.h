#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>

/**
 * @class Vector2
 * @brief A template class for a 2D vector.
 *
 * This class represents a two-dimensional vector and provides various
 * vector operations such as addition, subtraction, scalar multiplication,
 * dot product, and more.
 */
template<typename T>
class Vector2 {
public:
    T x, y; ///< The x and y components of the vector.

    /// @name Constructors
    /// @{
    
    /**
     * @brief Default constructor.
     * Initializes both components to zero.
     */
    constexpr Vector2();

    /**
     * @brief Parameterized constructor.
     * @param x The x component.
     * @param y The y component.
     */
    constexpr Vector2(T x, T y);
    
    /// @}

    /// @name Copy and Move Operations
    /// @{
    
    /**
     * @brief Default copy constructor.
     */
    Vector2(const Vector2&) = default;

    /**
     * @brief Default copy assignment operator.
     */
    Vector2& operator=(const Vector2&) = default;

    /**
     * @brief Default move constructor.
     */
    Vector2(Vector2&&) = default;

    /**
     * @brief Default move assignment operator.
     */
    Vector2& operator=(Vector2&&) = default;

    /// @}

    /// @name Array Subscript Operator
    /// @{
    
    /**
     * @brief Accesses a component of the vector.
     * @param i Index (0 for x, 1 for y).
     * @return Reference to the component.
     */
    T& operator[](int i);

    /**
     * @brief Accesses a component of the vector (const version).
     * @param i Index (0 for x, 1 for y).
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
    Vector2 operator+(const Vector2& v) const;

    /**
     * @brief Subtracts a vector from this vector.
     * @param v The vector to subtract.
     * @return The resulting vector.
     */
    Vector2 operator-(const Vector2& v) const;

    /**
     * @brief Adds a vector to this vector.
     * @param v The vector to add.
     * @return Reference to this vector.
     */
    Vector2& operator+=(const Vector2& v);

    /**
     * @brief Subtracts a vector from this vector.
     * @param v The vector to subtract.
     * @return Reference to this vector.
     */
    Vector2& operator-=(const Vector2& v);

    /// @}

    /// @name Scalar Multiplication and Division
    /// @{
    
    /**
     * @brief Multiplies the vector by a scalar.
     * @param s The scalar value.
     * @return The resulting vector.
     */
    Vector2 operator*(T s) const;

    /**
     * @brief Divides the vector by a scalar.
     * @param s The scalar value.
     * @return The resulting vector.
     */
    Vector2 operator/(T s) const;

    /**
     * @brief Multiplies this vector by a scalar.
     * @param s The scalar value.
     * @return Reference to this vector.
     */
    Vector2& operator*=(T s);

    /**
     * @brief Divides this vector by a scalar.
     * @param s The scalar value.
     * @return Reference to this vector.
     */
    Vector2& operator/=(T s);

    /**
     * @brief Multiplies two vectors component-wise.
     * @param other The vector to multiply with.
     * @return The resulting vector.
     */
    Vector2 operator*(const Vector2& other) const;

    /// @}

    /// @name Dot Product
    /// @{
    
    /**
     * @brief Computes the dot product with another vector.
     * @param v The other vector.
     * @return The dot product.
     */
    T dot(const Vector2& v) const;

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
    Vector2 normalized() const;

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
    bool operator==(const Vector2& v) const;

    /**
     * @brief Checks if two vectors are not equal.
     * @param v The vector to compare with.
     * @return True if not equal, false otherwise.
     */
    bool operator!=(const Vector2& v) const;

    /// @}

    /// @name Utility Functions
    /// @{
    
    /**
     * @brief Linearly interpolates between two vectors.
     * @param a The start vector.
     * @param b The end vector.
     * @param t The interpolation factor [0, 1].
     * @return The interpolated vector.
     */
    static Vector2 lerp(const Vector2& a, const Vector2& b, T t);

    /**
     * @brief Returns a vector with both components set to zero.
     * @return The zero vector.
     */
    static constexpr Vector2 zero();

    /**
     * @brief Returns a vector with both components set to one.
     * @return The one vector.
     */
    static constexpr Vector2 one();

    /**
     * @brief Returns a unit vector pointing in the X direction.
     * @return The unit vector in the X direction.
     */
    static constexpr Vector2 unitX();

    /**
     * @brief Returns a unit vector pointing in the Y direction.
     * @return The unit vector in the Y direction.
     */
    static constexpr Vector2 unitY();

    /// @}

    /// @name Stream Output
    /// @{
    
    /**
     * @brief Overload of the stream insertion operator for Vector2.
     * @param os The output stream.
     * @param v The vector to output.
     * @return The output stream.
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector2<U>& v);

    /// @}
};

// Scalar multiplication (scalar * vector)
template<typename T>
Vector2<T> operator*(T s, const Vector2<T>& v);

// Commonly used types
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;

#include "Vector2.inl"

#endif // VECTOR2_H
