#ifndef VECTOR3_INL
#define VECTOR3_INL

template<typename T>
constexpr Vector3<T>::Vector3() : x(0), y(0), z(0) {}

template<typename T>
constexpr Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

template<typename T>
T& Vector3<T>::operator[](int i) {
    if (i < 0 || i > 2) throw std::out_of_range("Vector3 index out of range");
    return (&x)[i];
}

template<typename T>
const T& Vector3<T>::operator[](int i) const {
    if (i < 0 || i > 2) throw std::out_of_range("Vector3 index out of range");
    return (&x)[i];
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v) {
    x += v.x; y += v.y; z += v.z;
    return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v) {
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator*(T s) const {
    return Vector3(x * s, y * s, z * s);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(T s) const {
    if (std::abs(s) < std::numeric_limits<T>::epsilon())
        throw std::invalid_argument("Division by zero in Vector3");
    return Vector3(x / s, y / s, z / s);
}

template<typename T>
Vector3<T>& Vector3<T>::operator*=(T s) {
    x *= s; y *= s; z *= s;
    return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator/=(T s) {
    if (std::abs(s) < std::numeric_limits<T>::epsilon())
        throw std::invalid_argument("Division by zero in Vector3");
    x /= s; y /= s; z /= s;
    return *this;
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);
}

template<typename T>
T Vector3<T>::dot(const Vector3<T>& v) const {
    return x * v.x + y * v.y + z * v.z;
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3<T>& v) const {
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

template<typename T>
T Vector3<T>::lengthSquared() const {
    return x * x + y * y + z * z;
}

template<typename T>
T Vector3<T>::length() const {
    return std::sqrt(lengthSquared());
}

template<typename T>
Vector3<T> Vector3<T>::normalized() const {
    T len = length();
    if (len < std::numeric_limits<T>::epsilon())
        throw std::domain_error("Cannot normalize zero-length Vector3");
    return *this / len;
}

template<typename T>
void Vector3<T>::normalize() {
    T len = length();
    if (len < std::numeric_limits<T>::epsilon())
        throw std::domain_error("Cannot normalize zero-length Vector3");
    *this /= len;
}

template<typename T>
bool Vector3<T>::operator==(const Vector3<T>& v) const {
    return std::abs(x - v.x) < std::numeric_limits<T>::epsilon() &&
           std::abs(y - v.y) < std::numeric_limits<T>::epsilon() &&
           std::abs(z - v.z) < std::numeric_limits<T>::epsilon();
}

template<typename T>
bool Vector3<T>::operator!=(const Vector3<T>& v) const {
    return !(*this == v);
}

template<typename T>
Vector3<T> Vector3<T>::projectOnto(const Vector3<T>& v) const {
    T lenSquared = v.lengthSquared();
    if (lenSquared < std::numeric_limits<T>::epsilon())
        throw std::invalid_argument("Cannot project onto zero-length vector");
    return v * (this->dot(v) / lenSquared);
}

template<typename T>
Vector3<T> Vector3<T>::reflect(const Vector3<T>& normal) const {
    return *this - normal * (2 * this->dot(normal));
}

template<typename T>
Vector3<T> Vector3<T>::lerp(const Vector3<T>& a, const Vector3<T>& b, T t) {
    return a + (b - a) * t;
}

template<typename T>
Vector3<T> Vector3<T>::slerp(const Vector3<T>& a, const Vector3<T>& b, T t) {
    T dot = a.dot(b);
    dot = std::clamp(dot, T(-1), T(1));
    T theta = std::acos(dot) * t;
    Vector3 relativeVec = (b - a * dot).normalized();
    return a * std::cos(theta) + relativeVec * std::sin(theta);
}

template<typename T>
constexpr Vector3<T> Vector3<T>::zero() { return Vector3(0, 0, 0); }

template<typename T>
constexpr Vector3<T> Vector3<T>::one() { return Vector3(1, 1, 1); }

template<typename T>
constexpr Vector3<T> Vector3<T>::up() { return Vector3(0, 1, 0); }

template<typename T>
constexpr Vector3<T> Vector3<T>::down() { return Vector3(0, -1, 0); }

template<typename T>
constexpr Vector3<T> Vector3<T>::left() { return Vector3(-1, 0, 0); }

template<typename T>
constexpr Vector3<T> Vector3<T>::right() { return Vector3(1, 0, 0); }

template<typename T>
constexpr Vector3<T> Vector3<T>::forward() { return Vector3(0, 0, 1); }

template<typename T>
constexpr Vector3<T> Vector3<T>::backward() { return Vector3(0, 0, -1); }

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
    return os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
}

template<typename T>
Vector3<T> operator*(T s, const Vector3<T>& v) {
    return v * s;
}

#endif // VECTOR3_INL
