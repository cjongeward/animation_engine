#ifndef SHAPES_H_
#define SHAPES_H_

#include <optional>
#include <vector>
#include "vec.hpp"
#include "Settings.h"


class Screen {
public:
	vec pos{ -5.f, -4.f, 0.f };
	float sizex = 10.f;
	float sizey = 8.f;
	int resx = SCREEN_RES_X;
	int resy = SCREEN_RES_Y;
};

class Material {
public:
  float difuse_mult;
  float spec_mult;
  float reflect_mult;
  float spec_coef;
  Material(float difuse, float spec, float reflect, float spec_exp) : 
    difuse_mult{ difuse }, spec_mult{ spec }, reflect_mult{ reflect }, spec_coef{ spec_exp } {}
};

vec reflection(const vec& orig, const vec& norm);

class Shape {
public:
  Material material;
	vec pos;
	vec color;
	bool bLightSource = false;

  Shape(const vec& t_pos, const vec& t_color, const Material& t_material, bool t_bLightSource) :
    pos{ t_pos },
    color{ t_color },
    material{ t_material },
    bLightSource{ t_bLightSource }
  {}

  virtual std::optional<ReflectionData> intersectsWith(Ray incident) = 0;
};

class Sphere : public Shape {
public:
	float radius;
  Sphere(const vec& t_pos, float t_radius, const vec& t_color, const Material& t_material, bool t_bLightSource) :
    Shape(t_pos, t_color, t_material, t_bLightSource),
    radius{ t_radius }
  {}
  std::optional<ReflectionData> intersectsWith(Ray incident) override;
};

class Plane : public Shape {
public:
  vec norm;
  Plane(const vec& t_pos, const vec& t_norm, const vec& t_color, const Material& t_material, bool t_bLightSource) :
    Shape(t_pos, t_color, t_material, t_bLightSource),
    norm{ t_norm }
  {}
  std::optional<ReflectionData> intersectsWith(Ray incident) override;
};

class AARect : public Shape {
public:
  vec size;
  AARect(const vec& t_pos, const vec& t_size, const vec& t_color, const Material& t_material, bool t_bLightSource) :
    Shape(t_pos, t_color, t_material, t_bLightSource),
    size{ t_size }
  {}
  std::optional<ReflectionData> intersectsWith(Ray incident) override;
};

std::optional<ReflectionData> intersects(Ray incident, Sphere s);
std::optional<ReflectionData> intersects(Ray incident, Plane p);
std::optional<ReflectionData> intersects(Ray incident, AARect r);




#endif
