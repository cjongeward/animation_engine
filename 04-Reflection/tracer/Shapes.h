#ifndef SHAPES_H_
#define SHAPES_H_

#include <optional>
#include "vec.h"
#include "Color.h"
#include "Reflection.h"

struct SurfaceProperties {
  Color color;
  float diffuse_factor;
  float specular_factor;
  float specular_exp;
  float reflect_factor;
  SurfaceProperties(const Color& t_color, float t_diffuse, float t_spec, float t_spec_exp, float t_reflect) :
    color{ t_color },
    diffuse_factor{ t_diffuse },
    specular_factor{ t_spec },
    specular_exp{ t_spec_exp },
    reflect_factor{ t_reflect }
  {}
};

const SurfaceProperties MIRRORISH{ GREY, 0.3f, 1.0f, 100.f, 0.9f };
const SurfaceProperties DULL{ GREEN, 0.5f, 0.05f, 10.f, 0.0f };
const SurfaceProperties BRIGHT{ PURPLE, 0.5f, 0.7f, 100.f, 0.1f };
const SurfaceProperties LIGHT{ WHITE, 1.0f, 1.0f, 100.f, 0.0f };



struct Ray {
  vec pos;
  vec dir;
  Ray(const vec& t_pos, const vec& t_dir) : pos{ t_pos }, dir{ t_dir } {}
};

struct Sphere {
  SurfaceProperties properties;
  vec pos;
  float radius;
  bool bIsLightSource = false;
  Sphere(const vec& t_pos, const SurfaceProperties& t_properties, float t_radius) : pos{ t_pos }, properties{ t_properties }, radius{ t_radius } {}
};

struct Screen {
  vec pos;
  float sizex;
  float sizey;
  Screen(const vec& t_pos, float t_sizex, float t_sizey) : pos{ t_pos }, sizex{ t_sizex }, sizey{ t_sizey }{}
};

struct ReflectionData {
  Ray reflection;
  vec norm;
  ReflectionData(const Ray& t_reflection, const vec& t_norm) : reflection{ t_reflection }, norm{ t_norm }{}
};

std::optional<ReflectionData> intersects(Sphere s, Ray incident);


#endif
