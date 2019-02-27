#ifndef VEC_H_
#define VEC_H_
#include <cmath>
#include <algorithm>

class vec {
public:
	float x, y, z;
	vec(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z } {}
  void clamp() {
    x = std::min(1.f, std::max(0.f, x));
    y = std::min(1.f, std::max(0.f, y));
    z = std::min(1.f, std::max(0.f, z));
  }
	float mag2() const {
		return x * x + y * y + z * z;
	}
	float mag() const {
		return std::sqrtf(mag2());
	}
	float dot(const vec& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
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

unsigned int toColor(const vec& v);

class matrix {
public:
	float vals[9];

	matrix(float _psi, float _theta, float _phi) {
		vals[0] = cosf(_psi) * cosf(_theta);
		vals[1] = sinf(_theta);
		vals[2] = -sinf(_psi);
		vals[3] = -sinf(_theta);
		vals[4] = cosf(_theta) * cosf(_phi);
		vals[5] = -sinf(_phi);
		vals[6] = sinf(_psi);
		vals[7] = sinf(_phi);
		vals[8] = cosf(_psi) * cosf(_phi);
	}

	vec operator*(const vec& rhs) {
		vec ans{ vals[0] * rhs.x + vals[1] * rhs.y + vals[2] * rhs.z,
		  vals[3] * rhs.x + vals[4] * rhs.y + vals[5] * rhs.z,
		  vals[6] * rhs.x + vals[7] * rhs.y + vals[8] * rhs.z };
		return ans;
	}
};

class Ray {
public:
	vec pos;
	vec dir;
	Ray(float px, float py, float pz, float dx, float dy, float dz) :
		pos{ px, py, pz }, dir{ dx, dy, dz } {
		dir.normalize();
	}
	Ray(const vec& _pos, const vec& _dir) : pos{ _pos }, dir{ _dir } {
		dir.normalize();
	}
};

struct ReflectionData {
  Ray reflectionRay;
  vec norm;
  ReflectionData(Ray ray, vec n) : reflectionRay{ std::move(ray) }, norm{ std::move(n) } {}
};



#endif
