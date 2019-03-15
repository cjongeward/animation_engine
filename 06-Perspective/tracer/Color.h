#ifndef COLOR_H_
#define COLOR_H_

#include "vec.h"

class Color {
  vec color_vec;

public:
  constexpr Color(float red, float green, float blue) : color_vec{ red, green, blue } {}
  constexpr void clamp() {
    color_vec.x = std::min(1.f, std::max(0.f, color_vec.x));
    color_vec.y = std::min(1.f, std::max(0.f, color_vec.y));
    color_vec.z = std::min(1.f, std::max(0.f, color_vec.z));
  }
  constexpr operator unsigned() const {
    Color temp_color = *this;
    temp_color.clamp();
    return (static_cast<unsigned>(255. * temp_color.color_vec.z) << 8) + 
      (static_cast<unsigned>(255. * temp_color.color_vec.y) << 16) + 
      (static_cast<unsigned>(255. * temp_color.color_vec.x) << 24);
  }

  constexpr Color& operator+=(const Color& rhs) {
    color_vec += rhs.color_vec;
    return *this;
  }
  constexpr Color operator+(const Color& rhs) const {
    Color ret = *this;
    ret += rhs;
    return ret;
  }
  constexpr Color operator*(float rhs) const {
    Color ret = *this;
    ret.color_vec *= rhs;
    return ret;
  }
};

constexpr Color RED{ 0.7f, 0.1f, 0.1f };
constexpr Color GREEN{ 0.1f, 0.7f, 0.1f };
constexpr Color PURPLE{ 0.7f, 0.1f, 0.7f };
constexpr Color WHITE{ 1.f, 1.f, 1.f };
constexpr Color GREY{ 0.2f, 0.2f, 0.2f };
constexpr Color LIGHTGREY{ 0.7f, 0.7f, 0.7f };
constexpr Color REALLYLIGHTGREY{ 0.8f, 0.8f, 0.8f };
constexpr Color BLACK{ 0.f, 0.f, 0.f };
constexpr Color TURQUOISE{ 0.1f, 0.8f, 0.8f };

#endif
