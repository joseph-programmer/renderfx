#ifndef GEOMETRY_INL
#define GEOMETRY_INL

#include <cmath>
#include <limits>

template<typename T>
constexpr Ray<T>::Ray() noexcept : origin(Vector3<T>::zero()), direction(Vector3<T>::forward()) {}

template<typename T>
constexpr Ray<T>::Ray(const Vector3<T>& origin, const Vector3<T>& direction)
    : origin(origin), direction(direction.normalized()) {}

template<typename T>
constexpr Vector3<T> Ray<T>::getPoint(T t) const noexcept {
    return origin + direction * t;
}

template<typename T>
constexpr AABB<T>::AABB() noexcept : min(Vector3<T>::zero()), max(Vector3<T>::zero()) {}

template<typename T>
constexpr AABB<T>::AABB(const Vector3<T>& min, const Vector3<T>& max) noexcept : min(min), max(max) {}

template<typename T>
bool AABB<T>::intersects(const Ray<T>& ray, T& tMin, T& tMax) const noexcept {
    tMin = -std::numeric_limits<T>::infinity();
    tMax = std::numeric_limits<T>::infinity();

    for (int i = 0; i < 3; ++i) {
        if (std::abs(ray.direction[i]) < std::numeric_limits<T>::epsilon()) {
            if (ray.origin[i] < min[i] || ray.origin[i] > max[i]) {
                return false;
            }
        }
        else {
            T t1 = (min[i] - ray.origin[i]) / ray.direction[i];
            T t2 = (max[i] - ray.origin[i]) / ray.direction[i];

            if (t1 > t2) std::swap(t1, t2);

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax) return false;
        }
    }

    return true;
}

template<typename T>
constexpr bool AABB<T>::contains(const Vector3<T>& point) const noexcept {
    return point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y &&
        point.z >= min.z && point.z <= max.z;
}

template<typename T>
constexpr Plane<T>::Plane() noexcept : normal(Vector3<T>::up()), distance(T(0)) {}

template<typename T>
constexpr Plane<T>::Plane(const Vector3<T>& normal, T distance) noexcept
    : normal(normal.normalized()), distance(distance) {}

template<typename T>
constexpr Plane<T>::Plane(const Vector3<T>& normal, const Vector3<T>& point) noexcept
    : normal(normal.normalized()), distance(-normal.dot(point)) {}

template<typename T>
constexpr T Plane<T>::distanceToPoint(const Vector3<T>& point) const noexcept {
    return normal.dot(point) + distance;
}

template<typename T>
bool Plane<T>::intersects(const Ray<T>& ray, T& t) const noexcept {
    T denom = normal.dot(ray.direction);
    if (std::abs(denom) < std::numeric_limits<T>::epsilon()) {
        return false;  // Ray is parallel to the plane
    }
    t = -(normal.dot(ray.origin) + distance) / denom;
    return t >= T(0);
}

template<typename T>
constexpr Sphere<T>::Sphere() noexcept : center(Vector3<T>::zero()), radius(T(1)) {}

template<typename T>
constexpr Sphere<T>::Sphere(const Vector3<T>& center, T radius) noexcept : center(center), radius(radius) {}

template<typename T>
constexpr bool Sphere<T>::contains(const Vector3<T>& point) const noexcept {
    return (point - center).lengthSquared() <= radius * radius;
}

template<typename T>
bool Sphere<T>::intersects(const Ray<T>& ray, T& t) const noexcept {
    Vector3<T> m = ray.origin - center;
    T b = m.dot(ray.direction);
    T c = m.dot(m) - radius * radius;

    if (c > T(0) && b > T(0)) return false;

    T discriminant = b * b - c;
    if (discriminant < T(0)) return false;

    t = -b - std::sqrt(discriminant);
    if (t < T(0)) t = T(0);
    return true;
}

template<typename T>
Frustum<T>::Frustum(const Matrix4x4<T>& viewProjection) {
    updatePlanes(viewProjection);
}

template<typename T>
void Frustum<T>::updatePlanes(const Matrix4x4<T>& viewProjection) noexcept {
    for (int i = 0; i < 3; ++i) {
        planes[0].normal[i] = viewProjection(i, 2) + viewProjection(i, 3);
        planes[1].normal[i] = -viewProjection(i, 2) + viewProjection(i, 3);
        planes[2].normal[i] = viewProjection(i, 0) + viewProjection(i, 3);
        planes[3].normal[i] = -viewProjection(i, 0) + viewProjection(i, 3);
        planes[4].normal[i] = viewProjection(i, 1) + viewProjection(i, 3);
        planes[5].normal[i] = -viewProjection(i, 1) + viewProjection(i, 3);
    }

    for (int i = 0; i < 6; ++i) {
        planes[i].distance = viewProjection(3, 3) - viewProjection(3, i / 2);
        T length = planes[i].normal.length();
        planes[i].normal /= length;
        planes[i].distance /= length;
    }
}

template<typename T>
bool Frustum<T>::contains(const Vector3<T>& point) const noexcept {
    for (const auto& plane : planes) {
        if (plane.distanceToPoint(point) < T(0)) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Frustum<T>::intersects(const AABB<T>& aabb) const noexcept {
    for (const auto& plane : planes) {
        Vector3<T> positive = aabb.min;
        if (plane.normal.x >= 0) positive.x = aabb.max.x;
        if (plane.normal.y >= 0) positive.y = aabb.max.y;
        if (plane.normal.z >= 0) positive.z = aabb.max.z;

        if (plane.distanceToPoint(positive) < T(0)) {
            return false;
        }
    }
    return true;
}

template<typename T>
constexpr Transform<T>::Transform() noexcept
    : position(Vector3<T>::zero()), rotation(Quaternion<T>()), scale(Vector3<T>::one()) {}

template<typename T>
constexpr Transform<T>::Transform(const Vector3<T>& position, const Quaternion<T>& rotation, const Vector3<T>& scale) noexcept
    : position(position), rotation(rotation), scale(scale) {}

template<typename T>
Matrix4x4<T> Transform<T>::toMatrix() const noexcept {
    return Matrix4x4<T>::translation(position) *
        rotation.toRotationMatrix() *
        Matrix4x4<T>::scaling(scale);
}

template<typename T>
Vector3<T> Transform<T>::transformPoint(const Vector3<T>& point) const noexcept {
    return rotation * (point * scale) + position;
}

template<typename T>
Vector3<T> Transform<T>::transformDirection(const Vector3<T>& direction) const noexcept {
    return rotation * direction;
}

template<typename T>
Transform<T> Transform<T>::interpolate(const Transform& other, T t) const noexcept {
    return Transform(
        Vector3<T>::lerp(position, other.position, t),
        Quaternion<T>::slerp(rotation, other.rotation, t),
        Vector3<T>::lerp(scale, other.scale, t)
    );
}

#endif // GEOMETRY_INL
