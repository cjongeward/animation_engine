#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <vector>
#include <memory>
#include "Scene.h"
#include "Shapes.h"
#include "Color.h"
#include "Settings.h"


class RayTracer {
private:
  const Ray primary_ray;
  const Color background_color = TURQUOISE;
  const float ambient_light_intensity = AMBIENT_LIGHT_INTENSITY;
  const int max_depth = MAX_RECURSIVE_DEPTH;

  Color trace(const Scene& scene, const Ray& incidentRay, int depth, const ShapeID& curShape) const;

public:
  RayTracer(const Ray& t_primary) : primary_ray{ t_primary } {}
  Color trace(const Scene& scene) const;
};



#endif
