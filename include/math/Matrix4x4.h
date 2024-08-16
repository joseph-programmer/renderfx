#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <array>
#include "Vector3.h"

/**
 * @brief A 4x4 matrix class template.
 * 
 * This class represents a 4x4 matrix and provides various matrix operations.
 * 
 * @tparam T Type of the elements in the matrix.
 */
template<typename T>
class Matrix4x4 {
public:
    /// The matrix data stored as a 2D array.
    std::array<std::array<T, 4>, 4> data;

    /**
     * @brief Default constructor. Initializes the matrix with zeroes.
     */
    constexpr Matrix4x4();

    /**
     * @brief Constructor that initializes the matrix with a 1D array of 16 values.
     * 
     * @param values An array containing 16 elements to initialize the matrix.
     */
    Matrix4x4(const std::array<T, 16>& values);

    /**
     * @brief Accesses an element of the matrix.
     * 
     * @param row The row index.
     * @param col The column index.
     * @return Reference to the element at the specified position.
     */
    T& operator()(int row, int col);

    /**
     * @brief Accesses an element of the matrix (const version).
     * 
     * @param row The row index.
     * @param col The column index.
     * @return Constant reference to the element at the specified position.
     */
    const T& operator()(int row, int col) const;

    /**
     * @brief Multiplies this matrix by another matrix.
     * 
     * @param other The matrix to multiply by.
     * @return The result of the matrix multiplication.
     */
    Matrix4x4 operator*(const Matrix4x4& other) const;

    /**
     * @brief Multiplies this matrix by a vector.
     * 
     * @param vec The vector to multiply by.
     * @return The transformed vector.
     */
    Vector3<T> operator*(const Vector3<T>& vec) const;

    /**
     * @brief Sets this matrix to the identity matrix.
     */
    void setIdentity();

    /**
     * @brief Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Matrix4x4 transposed() const;

    /**
     * @brief Creates an identity matrix.
     * 
     * @return The identity matrix.
     */
    static Matrix4x4 identity();

    /**
     * @brief Creates a translation matrix.
     * 
     * @param translation The translation vector.
     * @return The translation matrix.
     */
    static Matrix4x4 translation(const Vector3<T>& translation);

    /**
     * @brief Creates a scaling matrix.
     * 
     * @param scale The scaling vector.
     * @return The scaling matrix.
     */
    static Matrix4x4 scaling(const Vector3<T>& scale);

    /**
     * @brief Creates a rotation matrix around the X-axis.
     * 
     * @param angle The rotation angle in radians.
     * @return The rotation matrix.
     */
    static Matrix4x4 rotationX(T angle);

    /**
     * @brief Creates a rotation matrix around the Y-axis.
     * 
     * @param angle The rotation angle in radians.
     * @return The rotation matrix.
     */
    static Matrix4x4 rotationY(T angle);

    /**
     * @brief Creates a rotation matrix around the Z-axis.
     * 
     * @param angle The rotation angle in radians.
     * @return The rotation matrix.
     */
    static Matrix4x4 rotationZ(T angle);

    /**
     * @brief Creates a look-at matrix.
     * 
     * @param eye The position of the viewer.
     * @param center The point to look at.
     * @param up The up direction.
     * @return The look-at matrix.
     */
    static Matrix4x4 lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up);

    /**
     * @brief Creates an orthographic projection matrix.
     * 
     * @param left The left plane of the orthographic view.
     * @param right The right plane of the orthographic view.
     * @param bottom The bottom plane of the orthographic view.
     * @param top The top plane of the orthographic view.
     * @param nearVal The near plane.
     * @param farVal The far plane.
     * @return The orthographic projection matrix.
     */
    static Matrix4x4 orthographic(T left, T right, T bottom, T top, T nearVal, T farVal);

    /**
     * @brief Creates a perspective projection matrix.
     * 
     * @param fov The field of view angle in radians.
     * @param aspectRatio The aspect ratio.
     * @param near The near plane.
     * @param far The far plane.
     * @return The perspective projection matrix.
     */
    static Matrix4x4 perspective(T fov, T aspectRatio, T near, T far);

    /**
     * @brief Computes the inverse of this matrix.
     * 
     * @return The inverse of this matrix.
     */
    Matrix4x4 inverse() const;

    /**
     * @brief Computes the determinant of this matrix.
     * 
     * @return The determinant of the matrix.
     */
    T determinant() const;
};

// Commonly used types
using Matrix4f = Matrix4x4<float>;
using Matrix4d = Matrix4x4<double>;

#include "Matrix4x4.inl"

#endif // MATRIX4X4_H
