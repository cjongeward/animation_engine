#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <vector>
#include <memory>
#include "Shapes.h"
#include "Color.h"
#include "Settings.h"

std::pair<const Shape*, std::optional<ReflectionData>>
    findNearestHitPoint(const std::vector<std::unique_ptr<Shape>>& shapes, const Ray& incidentRay, const Shape* pIgnoreShape);

class RayTracer {
private:
  const Ray primary_ray;
  const Color background_color = TURQUOISE;
  const float ambient_light_intensity = AMBIENT_LIGHT_INTENSITY;
  const int max_depth = MAX_RECURSIVE_DEPTH;

  Color trace(const std::vector<std::unique_ptr<Shape>>& shapes, const Ray& incidentRay, int depth, const Shape* curShape) const;

public:
  RayTracer(const Ray& t_primary) : primary_ray{ t_primary } {}
  Color trace(const std::vector<std::unique_ptr<Shape>>& shapes) const;
};



#endif
