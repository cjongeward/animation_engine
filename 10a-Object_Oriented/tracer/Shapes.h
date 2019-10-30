#ifndef SHAPES_H_
#define SHAPES_H_

#include <optional>
#include "vec.h"
#include "SurfaceProperties.h"
#include "Reflection.h"
#include "MeshReader.h"

struct Ray {
  vec pos;
  vec dir;
  Ray(const vec& t_pos, const vec& t_dir) : pos{ t_pos }, dir{ t_dir } {}
};
// data packet containing important data from a reflection
struct ReflectionData {
  Ray reflection;
  vec norm;
  float u = 0.f;
  float v = 0.f;
  ReflectionData(const Ray& t_reflection, const vec& t_norm, float t_u, float t_v) : reflection{ t_reflection }, norm{ t_norm }, u{t_u}, v{t_v}{}
};

struct Shape {
  vec pos;
  SurfaceProperties properties;
  Shape(const vec& t_pos, const SurfaceProperties& t_properties) : pos{ t_pos }, properties{ t_properties } {}
  virtual std::optional<ReflectionData> intersects_with(const Ray& ray) const = 0;
  virtual void transform(const mat& xform) = 0;
};
struct Sphere : public Shape {
  float radius;
  Sphere(const vec& t_pos, const SurfaceProperties& t_properties, float t_radius) : Shape{ t_pos, t_properties }, radius{ t_radius } {}
  std::optional<ReflectionData> intersects_with(const Ray& ray) const override;
  void transform(const mat& xfrom) override {
    pos = xfrom * pos;
  }

};
struct Triangle : public Shape {
  vec pos2;
  vec pos3;
  vec p2mp1;
  vec p3mp1;
  vec norm;
  Triangle(const vec& t_pos, const vec& t_pos2, const vec& t_pos3, const SurfaceProperties& t_properties) :
    Shape{ t_pos, t_properties }, 
    pos2{ t_pos2 }, 
    pos3{ t_pos3 },
    p2mp1{ pos - pos2 },
    p3mp1{ pos - pos3 },
    norm{ -p3mp1.cross(p2mp1) }
  {
    norm.normalize();
  }
  std::optional<ReflectionData> intersects_with(const Ray& ray) const override;
  void transform(const mat& xfrom) override {
    pos = xfrom * pos;
    pos2 = xfrom * pos2;
    pos3 = xfrom * pos3;
    p2mp1 = pos - pos2;
    p3mp1 = pos - pos3;
    norm = -p3mp1.cross(p2mp1);
    norm.normalize();
  }
};
struct Rect : public Shape {
  vec pos2;
  vec pos3;
  vec p2mp1;
  vec p3mp1;
  vec norm;
  Rect(const vec& t_pos, const vec& t_pos2, const vec& t_pos3, const SurfaceProperties& t_properties) :
    Shape{ t_pos, t_properties }, 
    pos2{ t_pos2 }, 
    pos3{ t_pos3 },
    p2mp1{ pos - pos2 },
    p3mp1{ pos - pos3 },
    norm{ -p3mp1.cross(p2mp1) }
  { 
    norm.normalize();
  }
  std::optional<ReflectionData> intersects_with(const Ray& ray) const override;
  void transform(const mat& xfrom) override {
    pos = xfrom * pos;
    pos2 = xfrom * pos2;
    pos3 = xfrom * pos3;
    p2mp1 = pos - pos2;
    p3mp1 = pos - pos3;
    norm = -p3mp1.cross(p2mp1);
    norm.normalize();
  }
};

struct Box : public Shape {
  Rect rect0;
  Rect rect1;
  Rect rect2;
  Rect rect3;
  Rect rect4;
  Rect rect5;
  static constexpr vec blf {-0.5f, -0.5f, -0.5f};
  static constexpr vec blb {-0.5f, -0.5f, 0.5f};
  static constexpr vec tlf {-0.5f, 0.5f, -0.5f};
  static constexpr vec tlb {-0.5f, 0.5f, 0.5f};
  static constexpr vec brf {0.5f, -0.5f, -0.5f};
  static constexpr vec brb {0.5f, -0.5f, 0.5f};
  static constexpr vec trf {0.5f, 0.5f, -0.5f};
  static constexpr vec trb {0.5f, 0.5f, 0.5f};

  Box(const vec& t_pos, const SurfaceProperties& t_properties) :
    Shape{ t_pos, t_properties },
    rect0{blb + pos, brb + pos, tlb + pos, t_properties },
    rect1{brb + pos, brf + pos, trb + pos, t_properties },
    rect2{brf + pos, blf + pos, trf + pos, t_properties },
    rect3{blf + pos, blb + pos, tlf + pos, t_properties },
    rect4{tlb + pos, trb + pos, tlf + pos, t_properties },
    rect5{blf + pos, brf + pos, blb + pos, t_properties }
    {
    }

  std::optional<ReflectionData> intersects_with(const Ray& ray) const override;

  void transform(const mat& xfrom) override {
    rect0.transform(xfrom);
    rect1.transform(xfrom);
    rect2.transform(xfrom);
    rect3.transform(xfrom);
    rect4.transform(xfrom);
    rect5.transform(xfrom);
  }
};

struct Bunny : public Shape {
  std::vector<Triangle> triangles;

  Bunny(const vec& t_pos, const SurfaceProperties& t_properties) :
    Shape{ t_pos, t_properties },
    triangles{parseMesh("bunny_simple2.off")}
    { }

  std::optional<ReflectionData> intersects_with(const Ray& ray) const override;

  void transform(const mat& xfrom) override {
    for(auto& tri : triangles) {
      tri.transform(xfrom);
    }
  }
};



// This should probably go somewhere else
struct Screen {
  vec pos;
  float sizex;
  float sizey;
  Screen(const vec& t_pos, float t_sizex, float t_sizey) : pos{ t_pos }, sizex{ t_sizex }, sizey{ t_sizey }{}
};



#endif
