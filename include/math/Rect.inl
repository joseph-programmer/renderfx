#ifndef RECT_INL
#define RECT_INL

#include <algorithm>
#include <ostream>

template<typename T>
constexpr Rect<T>::Rect() : x(0), y(0), width(0), height(0) {}

template<typename T>
constexpr Rect<T>::Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}

template<typename T>
constexpr Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size)
    : x(position.x), y(position.y), width(size.x), height(size.y) {}

template<typename T>
constexpr T Rect<T>::left() const { return x; }

template<typename T>
constexpr T Rect<T>::right() const { return x + width; }

template<typename T>
constexpr T Rect<T>::top() const { return y; }

template<typename T>
constexpr T Rect<T>::bottom() const { return y + height; }

template<typename T>
constexpr Vector2<T> Rect<T>::position() const { return Vector2<T>(x, y); }

template<typename T>
constexpr Vector2<T> Rect<T>::size() const { return Vector2<T>(width, height); }

template<typename T>
constexpr Vector2<T> Rect<T>::center() const { return Vector2<T>(x + width / 2, y + height / 2); }

template<typename T>
constexpr bool Rect<T>::contains(const Vector2<T>& point) const {
    return point.x >= x && point.x < right() &&
           point.y >= y && point.y < bottom();
}

template<typename T>
constexpr bool Rect<T>::intersects(const Rect& other) const {
    return !(right() <= other.x || other.right() <= x ||
             bottom() <= other.y || other.bottom() <= y);
}

template<typename T>
Rect<T> Rect<T>::intersection(const Rect& other) const {
    T intersectLeft = std::max(x, other.x);
    T intersectTop = std::max(y, other.y);
    T intersectRight = std::min(right(), other.right());
    T intersectBottom = std::min(bottom(), other.bottom());

    if (intersectLeft < intersectRight && intersectTop < intersectBottom) {
        return Rect(intersectLeft, intersectTop,
                    intersectRight - intersectLeft,
                    intersectBottom - intersectTop);
    }
    return Rect(); // No intersection, return empty rectangle
}

template<typename T>
void Rect<T>::expand(const Vector2<T>& point) {
    T newX = std::min(x, point.x);
    T newY = std::min(y, point.y);
    width = std::max(right(), point.x) - newX;
    height = std::max(bottom(), point.y) - newY;
    x = newX;
    y = newY;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& r) {
    return os << "Rect(" << r.x << ", " << r.y << ", " << r.width << ", " << r.height << ")";
}

#endif // RECT_INL
