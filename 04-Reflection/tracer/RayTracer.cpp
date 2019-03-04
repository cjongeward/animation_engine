#include "RayTracer.h"

Color RayTracer::trace(const std::vector<Sphere>& shapes) {
  Color final_color = BLACK;
  bool bAnyColor = false;
  for (auto& shape : shapes) {
    if (auto reflected = intersects(shape, primary)) {
      bAnyColor = true;
      if (shape.bIsLightSource) {
        final_color = shape.color;
      }
      else {
        final_color = final_color + shape.color * AMBIENT_LIGHT_INTENSITY;
        for (auto& secondary_shape : shapes) {
          if (secondary_shape.bIsLightSource) {
            vec lightDir = secondary_shape.pos - reflected->reflection.pos;
            lightDir.normalize();
            float diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir));
            float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, reflected->norm)).dot(primary.dir)), 50.f);
            constexpr float diffuse_mult = 0.5f;
            constexpr float spec_mult = 0.8f;
            final_color = final_color + shape.color * diffuse_mult * diffuse_light_intensity + secondary_shape.color * spec_mult * specular_light_intensity;
          }
        }
      }
    }
  }
  if (!bAnyColor) {
    final_color = BACKGROUND_COLOR;
  }
  return final_color;
}

