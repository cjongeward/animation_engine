#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <vector>
#include "Shapes.h"
#include "Color.h"
#include "Settings.h"
const Color BACKGROUND_COLOR{ 0.1f, 0.3f, 0.7f };

class RayTracer {
  Ray primary;
  Color background_color = BACKGROUND_COLOR;
  float ambient_light_intensity = AMBIENT_LIGHT_INTENSITY;
  int max_depth = 5;

public:
  RayTracer(const Ray& t_primary) : primary{ t_primary } {}
  Color trace(const std::vector<Sphere>& shapes);
  Color trace(const std::vector<Sphere>& shapes, const Ray& incidentRay, int depth, const Sphere* curShape);
};



#endif
