#ifndef RAYGENERATOR_H_
#define RAYGENERATOR_H_
#include "vec.hpp"

class RayGenerator {
public:
  virtual Ray generateRay(const vec& point) = 0;
};

class OrthographicRayGenerator : public RayGenerator {
private:
  vec screen_norm;
public:
  OrthographicRayGenerator(const vec& t_screen_norm) :
    screen_norm{ t_screen_norm }
  { }
  Ray generateRay(const vec& point) override {
    return Ray{ point, screen_norm * -1.f };
  }
};

class PerspectiveRayGenerator : public RayGenerator {
private:
  vec screen_norm;
  vec screen_center_pos;
  float focal_dist;

public:
  PerspectiveRayGenerator(const vec& t_screen_norm, const vec& t_screen_center_pos, float t_focal_dist)  :
    screen_norm{ t_screen_norm },
    screen_center_pos{ t_screen_center_pos },
    focal_dist{ t_focal_dist }
  { }

  Ray generateRay(const vec& point) override {
    auto focal_pos = screen_center_pos + screen_norm * focal_dist;
    auto vec_to_pixel = point - focal_pos;
    vec_to_pixel.normalize();
    return Ray{ point, vec_to_pixel };
  }
};


#endif
