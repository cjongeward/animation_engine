#ifndef SHAPES_H_
#define SHAPES_H_

#include "vec.h"
#include "Color.h"

struct Ray {
  vec pos;
  vec dir;
  Ray(const vec& t_pos, const vec& t_dir) : pos{ t_pos }, dir{ t_dir } {}
};

struct Sphere {
  vec pos;
  Color color;
  float radius;
  Sphere(const vec& t_pos, const Color& t_color, float t_radius) : pos{ t_pos }, color{ t_color }, radius{ t_radius } {}
};

struct Screen {
  vec pos;
  float sizex;
  float sizey;
  Screen(const vec& t_pos, float t_sizex, float t_sizey) : pos{ t_pos }, sizex{ t_sizex }, sizey{ t_sizey }{}
};




#endif
