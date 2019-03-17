#ifndef RAYGENERATOR_H_
#define RAYGENERATOR_H_
#include "vec.h"
#include "Shapes.h"

// Generates a ray for each pixel on the screen
class RayGenerator {
public:
  virtual Ray MakeRay(int row, int col) const = 0;
};

class OrthographicRayGenerator : public RayGenerator {
private:
  Screen screen;
public:
  OrthographicRayGenerator(const Screen& t_screen) : screen{ t_screen } {}
  Ray MakeRay(int row, int col) const override;
};

class PerspectiveRayGenerator : public RayGenerator {
private:
  Screen screen;
  vec focal_point;
public:
  PerspectiveRayGenerator(const Screen& t_screen, const vec& t_focal_point) : focal_point{ t_focal_point }, screen{ t_screen }{}
  Ray MakeRay(int row, int col) const override;
};

#endif
