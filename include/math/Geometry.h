#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

/**
 * @brief A template class representing a ray in 3D space.
 * 
 * @tparam T Type of the elements in the vector.
 */
template<typename T>
class Ray {
public:
    Vector3<T> origin;    ///< The origin of the ray.
    Vector3<T> direction; ///< The direction of the ray.

    /**
     * @brief Default constructor. Initializes the ray with zero origin and direction.
     */
    constexpr Ray() noexcept;

    /**
     * @brief Constructor with specified origin and direction.
     * 
     * @param origin The origin of the ray.
     * @param direction The direction of the ray.
     */
    constexpr Ray(const Vector3<T>& origin, const Vector3<T>& direction);

    /**
     * @brief Gets a point along the ray at a distance t from the origin.
     * 
     * @param t The distance from the origin.
     * @return The point along the ray.
     */
    constexpr Vector3<T> getPoint(T t) const noexcept;
};

/**
 * @brief A template class representing an Axis-Aligned Bounding Box (AABB).
 * 
 * @tparam T Type of the elements in the vector.
 */
template<typename T>
class AABB {
public:
    Vector3<T> min; ///< The minimum corner of the AABB.
    Vector3<T> max; ///< The maximum corner of the AABB.

    /**
     * @brief Default constructor. Initializes the AABB with zero extents.
     */
    constexpr AABB() noexcept;

    /**
     * @brief Constructor with specified minimum and maximum corners.
     * 
     * @param min The minimum corner of the AABB.
     * @param max The maximum corner of the AABB.
     */
    constexpr AABB(const Vector3<T>& min, const Vector3<T>& max) noexcept;

    /**
     * @brief Checks if the AABB intersects with a given ray.
     * 
     * @param ray The ray to test for intersection.
     * @param tMin The distance to the nearest intersection point.
     * @param tMax The distance to the farthest intersection point.
     * @return True if there is an intersection, false otherwise.
     */
    bool intersects(const Ray<T>& ray, T& tMin, T& tMax) const noexcept;

    /**
     * @brief Checks if the AABB contains a given point.
     * 
     * @param point The point to check.
     * @return True if the point is inside the AABB, false otherwise.
     */
    constexpr bool contains(const Vector3<T>& point) const noexcept;
};

/**
 * @brief A template class representing a plane in 3D space.
 * 
 * @tparam T Type of the elements in the vector.
 */
template<typename T>
class Plane {
public:
    Vector3<T> normal; ///< The normal vector of the plane.
    T distance;        ///< The distance from the origin to the plane along the normal.

    /**
     * @brief Default constructor. Initializes the plane with a zero normal and distance.
     */
    constexpr Plane() noexcept;

    /**
     * @brief Constructor with specified normal and distance.
     * 
     * @param normal The normal vector of the plane.
     * @param distance The distance from the origin to the plane.
     */
    constexpr Plane(const Vector3<T>& normal, T distance) noexcept;

    /**
     * @brief Constructor with specified normal and a point on the plane.
     * 
     * @param normal The normal vector of the plane.
     * @param point A point on the plane.
     */
    constexpr Plane(const Vector3<T>& normal, const Vector3<T>& point) noexcept;

    /**
     * @brief Calculates the signed distance from a point to the plane.
     * 
     * @param point The point to calculate the distance from.
     * @return The signed distance from the point to the plane.
     */
    constexpr T distanceToPoint(const Vector3<T>& point) const noexcept;

    /**
     * @brief Checks if the plane intersects with a given ray.
     * 
     * @param ray The ray to test for intersection.
     * @param t The distance to the intersection point.
     * @return True if there is an intersection, false otherwise.
     */
    bool intersects(const Ray<T>& ray, T& t) const noexcept;
};

/**
 * @brief A template class representing a sphere in 3D space.
 * 
 * @tparam T Type of the elements in the vector.
 */
template<typename T>
class Sphere {
public:
    Vector3<T> center; ///< The center of the sphere.
    T radius;          ///< The radius of the sphere.

    /**
     * @brief Default constructor. Initializes the sphere with zero radius and center.
     */
    constexpr Sphere() noexcept;

    /**
     * @brief Constructor with specified center and radius.
     * 
     * @param center The center of the sphere.
     * @param radius The radius of the sphere.
     */
    constexpr Sphere(const Vector3<T>& center, T radius) noexcept;

    /**
     * @brief Checks if the sphere contains a given point.
     * 
     * @param point The point to check.
     * @return True if the point is inside the sphere, false otherwise.
     */
    constexpr bool contains(const Vector3<T>& point) const noexcept;

    /**
     * @brief Checks if the sphere intersects with a given ray.
     * 
     * @param ray The ray to test for intersection.
     * @param t The distance to the intersection point.
     * @return True if there is an intersection, false otherwise.
     */
    bool intersects(const Ray<T>& ray, T& t) const noexcept;
};

/**
 * @brief A template class representing a frustum in 3D space.
 * 
 * @tparam T Type of the elements in the vector.
 */
template<typename T>
class Frustum {
public:
    std::array<Plane<T>, 6> planes;  ///< The six planes defining the frustum.

    /**
     * @brief Default constructor.
     */
    Frustum() = default;

    /**
     * @brief Constructor with specified view-projection matrix.
     * 
     * @param viewProjection The view-projection matrix.
     */
    explicit Frustum(const Matrix4x4<T>& viewProjection);

    /**
     * @brief Updates the planes of the frustum based on a view-projection matrix.
     * 
     * @param viewProjection The view-projection matrix.
     */
    void updatePlanes(const Matrix4x4<T>& viewProjection) noexcept;

    /**
     * @brief Checks if the frustum contains a given point.
     * 
     * @param point The point to check.
     * @return True if the point is inside the frustum, false otherwise.
     */
    bool contains(const Vector3<T>& point) const noexcept;

    /**
     * @brief Checks if the frustum intersects with a given AABB.
     * 
     * @param aabb The AABB to test for intersection.
     * @return True if there is an intersection, false otherwise.
     */
    bool intersects(const AABB<T>& aabb) const noexcept;
};

/**
     * @brief A template class representing a transform in 3D space.
     * 
     * @tparam T Type of the elements in the vector.
     */
template<typename T>
class Transform {
public:
    Vector3<T> position;    ///< The position of the transform.
    Quaternion<T> rotation; ///< The rotation of the transform.
    Vector3<T> scale;       ///< The scale of the transform.

    /**
     * @brief Default constructor. Initializes the transform with identity values.
     */
    constexpr Transform() noexcept;

    /**
     * @brief Constructor with specified position, rotation, and scale.
     * 
     * @param position The position of the transform.
     * @param rotation The rotation of the transform.
     * @param scale The scale of the transform.
     */
    constexpr Transform(const Vector3<T>& position, const Quaternion<T>& rotation, const Vector3<T>& scale) noexcept;

    /**
     * @brief Converts the transform to a 4x4 matrix.
     * 
     * @return The transformation matrix.
     */
    Matrix4x4<T> toMatrix() const noexcept;

    /**
     * @brief Transforms a point by this transform.
     * 
     * @param point The point to transform.
     * @return The transformed point.
     */
    Vector3<T> transformPoint(const Vector3<T>& point) const noexcept;

    /**
     * @brief Transforms a direction by this transform.
     * 
     * @param direction The direction to transform.
     * @return The transformed direction.
     */
    Vector3<T> transformDirection(const Vector3<T>& direction) const noexcept;

    /**
     * @brief Interpolates between this transform and another transform.
     * 
     * @param other The other transform to interpolate with.
     * @param t The interpolation parameter, between 0 and 1.
     * @return The interpolated transform.
     */
    Transform interpolate(const Transform& other, T t) const noexcept;
};

// Commonly used types
using Rayf = Ray<float>;
using AABBf = AABB<float>;
using Planef = Plane<float>;
using Spheref = Sphere<float>;
using Frustumf = Frustum<float>;
using Transformf = Transform<float>;

#include "Geometry.inl"

#endif // GEOMETRY_H
