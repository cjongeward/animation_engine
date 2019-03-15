#ifndef SURFACEPROPERTIES_H_
#define SURFACEPROPERTIES_H_
#include "Color.h"

struct SurfaceProperties {
  Color color;
  float diffuse_factor;
  float specular_factor;
  float specular_exp;
  float reflect_factor;
  float intensity;
  constexpr SurfaceProperties(const Color& t_color, float t_diffuse, float t_spec, float t_spec_exp, float t_reflect, float t_intensity) :
    color{ t_color },
    diffuse_factor{ t_diffuse },
    specular_factor{ t_spec },
    specular_exp{ t_spec_exp },
    reflect_factor{ t_reflect },
    intensity{t_intensity}
  {}
};
constexpr SurfaceProperties MIRRORISH{ GREY, 0.4f, 0.0f, 100.f, 0.9f, 0.f };
constexpr SurfaceProperties DULL{ GREEN, 0.5f, 0.05f, 10.f, 0.0f, 0.f };
constexpr SurfaceProperties BRIGHT{ PURPLE, 0.5f, 0.7f, 100.f, 0.1f, 0.f };
constexpr SurfaceProperties LIGHT{ WHITE, 1.0f, 1.0f, 100.f, 0.0f, 1.f };
constexpr SurfaceProperties GRAYISH{ LIGHTGREY, 0.5f, 0.15f, 10.f, 0.0f, 0.f };
constexpr SurfaceProperties WHITEISH{ REALLYLIGHTGREY, 0.5f, 0.0f, 10.f, 0.0f, 0.f };
constexpr SurfaceProperties YELLOWISH{ Color{0.f, 0.6f, 0.3f}, 0.5f, 0.15f, 10.f, 0.0f, 0.f };


#endif
