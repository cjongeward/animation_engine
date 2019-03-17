#ifndef SHAPES_H_
#define SHAPES_H_

#include <optional>
#include "vec.h"
#include "SurfaceProperties.h"
#include "Reflection.h"

struct Ray {
  vec pos;
  vec dir;
  Ray(const vec& t_pos, const vec& t_dir) : pos{ t_pos }, dir{ t_dir } {}
};
struct ReflectionData {
  Ray reflection;
  vec norm;
  ReflectionData(const Ray& t_reflection, const vec& t_norm) : reflection{ t_reflection }, norm{ t_norm }{}
};

struct Shape {
  vec pos;
  SurfaceProperties properties;
  Shape(const vec& t_pos, const SurfaceProperties& t_properties) : pos{ t_pos }, properties{ t_properties } {}
  virtual std::optional<ReflectionData> intersects_with(const Ray& ray) const = 0;
};
struct Sphere : public Shape {
  float radius;
  Sphere(const vec& t_pos, const SurfaceProperties& t_properties, float t_radius) : Shape{ t_pos, t_properties }, radius{ t_radius } {}
  std::optional<ReflectionData> intersects_with(const Ray& ray) const override; 
};
struct Triangle : public Shape {
  vec pos2;
  vec pos3;
  Triangle(const vec& t_pos, const vec& t_pos2, const vec& t_pos3, const SurfaceProperties& t_properties) : 
    Shape{ t_pos, t_properties }, 
    pos2{ t_pos2 }, 
    pos3{ t_pos3 }
  {}
  std::optional<ReflectionData> intersects_with(const Ray& ray) const override; 
};
struct Rect : public Shape {
  vec pos2;
  vec pos3;
  Rect(const vec& t_pos, const vec& t_pos2, const vec& t_pos3, const SurfaceProperties& t_properties) : 
    Shape{ t_pos, t_properties }, 
    pos2{ t_pos2 }, 
    pos3{ t_pos3 }
  {}
  std::optional<ReflectionData> intersects_with(const Ray& ray) const override; 
};

struct Screen {
  vec pos;
  float sizex;
  float sizey;
  Screen(const vec& t_pos, float t_sizex, float t_sizey) : pos{ t_pos }, sizex{ t_sizex }, sizey{ t_sizey }{}
};


std::optional<ReflectionData> intersects(const Sphere& sphere, const Ray& incident_ray);
std::optional<ReflectionData> intersects(const Triangle& triangle, const Ray& incident_ray);
std::optional<ReflectionData> intersects(const Rect& rect, const Ray& incident_ray);


#endif
