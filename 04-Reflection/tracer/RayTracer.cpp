#include "RayTracer.h"

Color RayTracer::trace(const std::vector<Sphere>& shapes) {
  return trace(shapes, primary, 0, nullptr);
}

Color RayTracer::trace(const std::vector<Sphere>& shapes, const Ray& incidentRay, int depth, const Sphere* curShape) {
  if (depth >= max_depth) {
    return BLACK;
  }
  Color final_color = BLACK;
  bool bAnyColor = false;
  for (auto& shape : shapes) {
    if (&shape != curShape) {
      if (auto reflected = intersects(shape, incidentRay)) {
        bAnyColor = true;
        if (shape.bIsLightSource) {
          final_color = shape.color;
        }
        else {
          constexpr float diffuse_mult = 0.2f;
          constexpr float spec_mult = 0.1f;
          constexpr float refl_mult = 0.5f;
          final_color += shape.color * ambient_light_intensity;
          Color reflected_color = trace(shapes, reflected->reflection, depth + 1, &shape);
          final_color += reflected_color * refl_mult;
          for (auto& secondary_shape : shapes) {
            if (secondary_shape.bIsLightSource) {
              vec lightDir = secondary_shape.pos - reflected->reflection.pos;
              lightDir.normalize();
              float diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir));
              float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, reflected->norm)).dot(primary.dir)), 50.f);
              final_color += shape.color * diffuse_mult * diffuse_light_intensity +
                secondary_shape.color * spec_mult * specular_light_intensity;
            }
          }
        }
      }
    }
  }
  if (!bAnyColor) {
    final_color = background_color;
  }
  return final_color;
}

