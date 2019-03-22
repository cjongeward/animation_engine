#include "RayTracer.h"

float myPow(float val, int exp) {
  int curexp = 1;
  float curval = val;
  while (curexp < exp) {
    curval *= curval;
    curexp *= 2;
  }
  return curval;
}

Color RayTracer::trace(const std::vector<std::unique_ptr<Shape>>& shapes) const {
  return trace(shapes, primary_ray, 0, nullptr);
}

Color RayTracer::trace(const std::vector<std::unique_ptr<Shape>>& shapes, const Ray& incidentRay, int depth, const Shape* curShape) const {
  if (depth >= max_depth) { // recursive base case
    return BLACK;
  }

  // find the nearest hit point
  const Shape* pNearestShape = nullptr;
  std::optional<ReflectionData> nearestReflection = std::nullopt;
  for (const auto& shape_up : shapes) {
    Shape* pShape = shape_up.get();
    Shape& shape = *pShape;
    if (&shape != curShape) {
      auto reflected = shape.intersects_with(incidentRay);
      if (reflected.has_value()) {
        if (!nearestReflection.has_value()) {
          pNearestShape = &shape;
          nearestReflection = reflected;
        }
        else if(dist2(reflected->reflection.pos, incidentRay.pos) < dist2(nearestReflection->reflection.pos, incidentRay.pos)) {
          pNearestShape = &shape;
          nearestReflection = reflected;
        }
      }
    }
  }

  // light it up
  Color final_color = BLACK;
  if (!nearestReflection.has_value()) {
    final_color = background_color;
  }
  else {
    final_color = pNearestShape->properties.color * pNearestShape->properties.intensity; // if shape is a light source
    final_color += pNearestShape->properties.color * ambient_light_intensity;
    Color reflected_color = trace(shapes, nearestReflection->reflection, depth + 1, pNearestShape);
    final_color += reflected_color * pNearestShape->properties.reflect_factor;
    for (auto& secondary_shape : shapes) {
      if (secondary_shape.get() != pNearestShape && secondary_shape->properties.intensity > 0.0f) {
        vec lightDir = secondary_shape->pos - nearestReflection->reflection.pos;
        lightDir.normalize();
        float diffuse_light_intensity = std::max(0.f, nearestReflection->norm.dot(lightDir)) * secondary_shape->properties.intensity;
        const auto r = -reflect(-lightDir, nearestReflection->norm);
        const auto rdotprim = std::max(0.f, r.dot(primary_ray.dir));
        float specular_light_intensity = myPow(rdotprim, pNearestShape->properties.specular_exp) * secondary_shape->properties.intensity;
        final_color += pNearestShape->properties.color * pNearestShape->properties.diffuse_factor * diffuse_light_intensity +
          secondary_shape->properties.color * pNearestShape->properties.specular_factor * specular_light_intensity;
      }
    }
  }
  return final_color;
}

