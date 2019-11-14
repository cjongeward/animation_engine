#ifndef VEC_H_
#define VEC_H_

#include <algorithm>
#include <cmath>

struct vec2 {
	float x, y;
	constexpr vec2(float _x, float _y) : x{_x}, y{_y} {}
};

class vec {
public:
  float x, y, z;
  constexpr vec(float _x, float _y, float _z) : x{ _x }, y{ _y }, z{ _z } {}
  constexpr float mag2() const {
    return x * x + y * y + z * z;
  }
  float mag() const {
    return std::sqrt(mag2());
  }
  constexpr float dot(const vec& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  constexpr vec cross(const vec& rhs) const {
    return vec(y*rhs.z - z * rhs.y, z*rhs.x - x * rhs.z, x*rhs.y - y * rhs.x);
  }
  void normalize() {
    auto overm = 1.0f / mag();
    x *= overm;
    y *= overm;
    z *= overm;
  }
  constexpr vec& operator-=(const vec& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }
  constexpr vec operator-(const vec& rhs) const {
    vec ret = *this;
    ret -= rhs;
    return ret;
  }
  constexpr vec& operator+=(const vec& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }
  constexpr vec operator+(const vec& rhs) const {
    vec ret = *this;
    ret += rhs;
    return ret;
  }
  constexpr vec& operator*=(float rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }
  constexpr vec operator*(float rhs) const {
    vec ret = *this;
    ret *= rhs;
    return ret;
  }
  constexpr vec operator-() const {
    vec ret = *this;
    ret *= -1.f;
    return ret;
  }
  constexpr vec& operator/=(float rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }
  constexpr vec operator/(float rhs) const {
    vec ret = *this;
    ret /= rhs;
    return ret;
  }
};

float dist2(const vec& v1, const vec& v2);

class mat {
private:
	float vals[16];

public:
	static mat identity() {
		return mat{1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f};
	}
	static mat rotation(float psi, float theta, float phi) {
		mat bank{std::cos(phi), -std::sin(phi), 0.f, 0.f,
		         std::sin(phi), std::cos(phi), 0.f, 0.f,
		         0.f, 0.f, 1.f, 0.f,
		         0.f, 0.f, 0.f, 1.f};
		mat pitch{1.f, 0.f, 0.f, 0.f,
		          0.f, std::cos(theta), -std::sin(theta), 0.f,
		          0.f, std::sin(theta), std::cos(theta), 0.f,
		          0.f, 0.f, 0.f, 1.f};
		mat yaw{std::cos(psi), 0.f, std::sin(psi), 0.f,
		        0.f, 1.f, 0.f, 0.f,
		        -std::sin(psi), 0.f, std::cos(psi), 0.f,
		        0.f, 0.f, 0.f, 1.f};
		return bank * pitch * yaw;
	}
	static mat translation(const vec& trans) {
	  return mat{1.f, 0.f, 0.f, trans.x,
	             0.f, 1.f, 0.f, trans.y,
	             0.f, 0.f, 1.f, trans.z,
	             0.f, 0.f, 0.f, 1.f};
	}
	static mat scale(const vec& s) {
	  return mat{s.x, 0.f, 0.f, 0.f,
	             0.f, s.y, 0.f, 0.f,
	             0.f, 0.f, s.z, 0.f,
	             0.f, 0.f, 0.f, 1.f};
	}

	mat(float e0,float e1,float e2,float e3,float e4,float e5,float e6,float e7,float e8,float e9,float ea,float eb,float ec,float ed, float ee,float ef) :
	  vals{e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,ea,eb,ec,ed,ee,ef}
	{ }
	vec operator*(const vec& rhs) const {
		return vec {vals[0]*rhs.x + vals[1]*rhs.y + vals[2]*rhs.z + vals[3],
			        vals[4]*rhs.x + vals[5]*rhs.y + vals[6]*rhs.z + vals[7],
			        vals[8]*rhs.x + vals[9]*rhs.y + vals[10]*rhs.z + vals[11]};
	}
	mat operator*(const mat& rhs) const {
		return mat {vals[0]*rhs.vals[0] + vals[1]*rhs.vals[4] + vals[2]*rhs.vals[8] + vals[3]*rhs.vals[12],
		            vals[0]*rhs.vals[1] + vals[1]*rhs.vals[5] + vals[2]*rhs.vals[9] + vals[3]*rhs.vals[13],
		            vals[0]*rhs.vals[2] + vals[1]*rhs.vals[6] + vals[2]*rhs.vals[10] + vals[3]*rhs.vals[14],
		            vals[0]*rhs.vals[3] + vals[1]*rhs.vals[7] + vals[2]*rhs.vals[11] + vals[3]*rhs.vals[15],

		            vals[4]*rhs.vals[0] + vals[5]*rhs.vals[4] + vals[6]*rhs.vals[8] + vals[7]*rhs.vals[12],
		            vals[4]*rhs.vals[1] + vals[5]*rhs.vals[5] + vals[6]*rhs.vals[9] + vals[7]*rhs.vals[13],
		            vals[4]*rhs.vals[2] + vals[5]*rhs.vals[6] + vals[6]*rhs.vals[10] + vals[7]*rhs.vals[14],
		            vals[4]*rhs.vals[3] + vals[5]*rhs.vals[7] + vals[6]*rhs.vals[11] + vals[7]*rhs.vals[15],

		            vals[8]*rhs.vals[0] + vals[9]*rhs.vals[4] + vals[10]*rhs.vals[8] + vals[11]*rhs.vals[12],
		            vals[8]*rhs.vals[1] + vals[9]*rhs.vals[5] + vals[10]*rhs.vals[9] + vals[11]*rhs.vals[13],
		            vals[8]*rhs.vals[2] + vals[9]*rhs.vals[6] + vals[10]*rhs.vals[10] + vals[11]*rhs.vals[14],
		            vals[8]*rhs.vals[3] + vals[9]*rhs.vals[7] + vals[10]*rhs.vals[11] + vals[11]*rhs.vals[15],

		            vals[12]*rhs.vals[0] + vals[13]*rhs.vals[4] + vals[14]*rhs.vals[8] + vals[15]*rhs.vals[12],
		            vals[12]*rhs.vals[1] + vals[13]*rhs.vals[5] + vals[14]*rhs.vals[9] + vals[15]*rhs.vals[13],
		            vals[12]*rhs.vals[2] + vals[13]*rhs.vals[6] + vals[14]*rhs.vals[10] + vals[15]*rhs.vals[14],
		            vals[12]*rhs.vals[3] + vals[13]*rhs.vals[7] + vals[14]*rhs.vals[11] + vals[15]*rhs.vals[15]};
	}
	mat& operator*=(const float rhs) {
	  for(int i = 0; i < 16; ++i) {
	    vals[i] *= rhs;
	  }
	  return *this;
	}

	float getMaxSizeEle() const {
	    float row1 = sqrtf(vals[0]*vals[0] + vals[1]*vals[1] + vals[2]*vals[2]);
        float row2 = sqrtf(vals[4]*vals[4] + vals[5]*vals[5] + vals[6]*vals[6]);
        float row3 = sqrtf(vals[8]*vals[8] + vals[9]*vals[9] + vals[10]*vals[10]);
        float max = fmaxf(row1, row2);
        max = fmaxf(max, row3);
        return max;
	}
};

struct Ray {
    vec pos;
    vec dir;
    Ray(const vec& t_pos, const vec& t_dir) : pos{ t_pos }, dir{ t_dir } {}
};

#endif
