#ifndef VECTOR2_INL
#define VECTOR2_INL

template<typename T>
constexpr Vector2<T>::Vector2() : x(0), y(0) {}

template<typename T>
constexpr Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template<typename T>
T& Vector2<T>::operator[](int i) {
    if (i < 0 || i > 1) throw std::out_of_range("Vector2 index out of range");
    return (i == 0) ? x : y;
}

template<typename T>
const T& Vector2<T>::operator[](int i) const {
    if (i < 0 || i > 1) throw std::out_of_range("Vector2 index out of range");
    return (i == 0) ? x : y;
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const {
    return Vector2(x + v.x, y + v.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const {
    return Vector2(x - v.x, y - v.y);
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& v) {
    x += v.x; y += v.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& v) {
    x -= v.x; y -= v.y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T s) const {
    return Vector2(x * s, y * s);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T s) const {
    if (std::abs(s) < std::numeric_limits<T>::epsilon())
        throw std::invalid_argument("Division by zero in Vector2");
    return Vector2(x / s, y / s);
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(T s) {
    x *= s; y *= s;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(T s) {
    if (std::abs(s) < std::numeric_limits<T>::epsilon())
        throw std::invalid_argument("Division by zero in Vector2");
    x /= s; y /= s;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& other) const {
    return Vector2(x * other.x, y * other.y);
}

template<typename T>
T Vector2<T>::dot(const Vector2<T>& v) const {
    return x * v.x + y * v.y;
}

template<typename T>
T Vector2<T>::lengthSquared() const {
    return x * x + y * y;
}

template<typename T>
T Vector2<T>::length() const {
    return std::sqrt(lengthSquared());
}

template<typename T>
Vector2<T> Vector2<T>::normalized() const {
    T len = length();
    if (len < std::numeric_limits<T>::epsilon())
        throw std::domain_error("Cannot normalize zero-length Vector2");
    return *this / len;
}

template<typename T>
void Vector2<T>::normalize() {
    T len = length();
    if (len < std::numeric_limits<T>::epsilon())
        throw std::domain_error("Cannot normalize zero-length Vector2");
    *this /= len;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& v) const {
    return std::abs(x - v.x) < std::numeric_limits<T>::epsilon() &&
           std::abs(y - v.y) < std::numeric_limits<T>::epsilon();
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& v) const {
    return !(*this == v);
}

template<typename T>
Vector2<T> Vector2<T>::lerp(const Vector2<T>& a, const Vector2<T>& b, T t) {
    return a + (b - a) * t;
}

template<typename T>
constexpr Vector2<T> Vector2<T>::zero() {
    return Vector2(0, 0);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::one() {
    return Vector2(1, 1);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::unitX() {
    return Vector2(1, 0);
}

template<typename T>
constexpr Vector2<T> Vector2<T>::unitY() {
    return Vector2(0, 1);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
    return os << "Vector2(" << v.x << ", " << v.y << ")";
}

template<typename T>
Vector2<T> operator*(T s, const Vector2<T>& v) {
    return v * s;
}

#endif // VECTOR2_INL
