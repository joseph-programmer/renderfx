#ifndef RECT_H
#define RECT_H

#include "Vector2.h"

/**
 * @brief A template class representing a rectangle.
 * 
 * This class defines a rectangle by its position and size, and provides
 * methods for various geometric operations such as intersection, containment,
 * and expansion.
 * 
 * @tparam T The data type for the rectangle's dimensions (e.g., float, double, int).
 */
template<typename T>
class Rect {
public:
    T x;       /**< The x-coordinate of the top-left corner of the rectangle. */
    T y;       /**< The y-coordinate of the top-left corner of the rectangle. */
    T width;   /**< The width of the rectangle. */
    T height;  /**< The height of the rectangle. */

    // Constructors

    /**
     * @brief Default constructor. Initializes the rectangle at (0, 0) with size (0, 0).
     */
    constexpr Rect();

    /**
     * @brief Constructs a rectangle with the given position and size.
     * 
     * @param x The x-coordinate of the top-left corner.
     * @param y The y-coordinate of the top-left corner.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    constexpr Rect(T x, T y, T width, T height);

    /**
     * @brief Constructs a rectangle from position and size vectors.
     * 
     * @param position A Vector2 representing the position (top-left corner).
     * @param size A Vector2 representing the size (width and height).
     */
    constexpr Rect(const Vector2<T>& position, const Vector2<T>& size);

    // Getters for derived properties

    /**
     * @brief Gets the x-coordinate of the left edge of the rectangle.
     * 
     * @return The left coordinate.
     */
    constexpr T left() const;

    /**
     * @brief Gets the x-coordinate of the right edge of the rectangle.
     * 
     * @return The right coordinate.
     */
    constexpr T right() const;

    /**
     * @brief Gets the y-coordinate of the top edge of the rectangle.
     * 
     * @return The top coordinate.
     */
    constexpr T top() const;

    /**
     * @brief Gets the y-coordinate of the bottom edge of the rectangle.
     * 
     * @return The bottom coordinate.
     */
    constexpr T bottom() const;

    /**
     * @brief Gets the position of the rectangle.
     * 
     * @return A Vector2 representing the position (top-left corner).
     */
    constexpr Vector2<T> position() const;

    /**
     * @brief Gets the size of the rectangle.
     * 
     * @return A Vector2 representing the size (width and height).
     */
    constexpr Vector2<T> size() const;

    /**
     * @brief Gets the center point of the rectangle.
     * 
     * @return A Vector2 representing the center point.
     */
    constexpr Vector2<T> center() const;

    // Check if a point is inside the rectangle

    /**
     * @brief Checks if a point is inside the rectangle.
     * 
     * @param point A Vector2 representing the point to check.
     * @return true if the point is inside the rectangle, false otherwise.
     */
    constexpr bool contains(const Vector2<T>& point) const;

    // Check if this rectangle intersects with another

    /**
     * @brief Checks if this rectangle intersects with another rectangle.
     * 
     * @param other The other rectangle to check against.
     * @return true if the rectangles intersect, false otherwise.
     */
    constexpr bool intersects(const Rect& other) const;

    // Get the intersection of this rectangle with another

    /**
     * @brief Gets the intersection of this rectangle with another.
     * 
     * @param other The other rectangle to intersect with.
     * @return A Rect representing the area of intersection.
     */
    Rect intersection(const Rect& other) const;

    // Expand the rectangle to include a point

    /**
     * @brief Expands the rectangle to include a given point.
     * 
     * @param point The point to include in the rectangle.
     */
    void expand(const Vector2<T>& point);

    // Stream output

    /**
     * @brief Outputs the rectangle to a stream.
     * 
     * @tparam U The data type of the rectangle's dimensions.
     * @param os The output stream.
     * @param r The rectangle to output.
     * @return A reference to the output stream.
     */
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Rect<U>& r);
};

// Commonly used types
using Rectf = Rect<float>;
using Rectd = Rect<double>;
using Recti = Rect<int>;

#include "Rect.inl"

#endif // RECT_H
