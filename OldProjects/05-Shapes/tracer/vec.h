#ifndef VEC_H_
#define VEC_H_

#include <algorithm>
#include <cmath>

class vec {
public:
  float x, y, z;
  vec(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z } {}
  float mag2() const {
    return x * x + y * y + z * z;
  }
  float mag() const {
    return std::sqrtf(mag2());
  }
  float dot(const vec& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  vec cross(const vec& rhs) const {
    return vec(y*rhs.z - z * rhs.y, z*rhs.x - x * rhs.z, x*rhs.y - y * rhs.x);
  }
  void normalize() {
    auto overm = 1.0f / mag();
    x *= overm;
    y *= overm;
    z *= overm;
  }
  vec& operator-=(const vec& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }
  vec operator-(const vec& rhs) const {
    vec ret = *this;
    ret -= rhs;
    return ret;
  }
  vec& operator+=(const vec& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }
  vec operator+(const vec& rhs) const {
    vec ret = *this;
    ret += rhs;
    return ret;
  }
  vec& operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }
  vec operator*(float rhs) const {
    vec ret = *this;
    ret *= rhs;
    return ret;
  }
  vec operator-() const {
    vec ret = *this;
    ret *= -1.f;
    return ret;
  }
  vec& operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }
  vec operator/(float rhs) const {
    vec ret = *this;
    ret /= rhs;
    return ret;
  }
};

float dist2(const vec& v1, const vec& v2);

#endif