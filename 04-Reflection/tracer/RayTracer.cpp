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
        final_color = shape.properties.color * shape.properties.intensity; // if shape is a light source
        final_color += shape.properties.color * ambient_light_intensity;
        Color reflected_color = trace(shapes, reflected->reflection, depth + 1, &shape);
        final_color += reflected_color * shape.properties.reflect_factor;
        for (auto& secondary_shape : shapes) {
          if (&secondary_shape != &shape) {
            vec lightDir = secondary_shape.pos - reflected->reflection.pos;
            lightDir.normalize();
            float diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir)) * secondary_shape.properties.intensity;
            float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, reflected->norm)).dot(primary.dir)), shape.properties.specular_exp) * secondary_shape.properties.intensity;
            final_color += shape.properties.color * shape.properties.diffuse_factor * diffuse_light_intensity +
              secondary_shape.properties.color * shape.properties.specular_factor * specular_light_intensity;
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

