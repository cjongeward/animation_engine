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

Color RayTracer::trace(const std::vector<DrawableShape>& shapes) const {
  return trace(shapes, primary_ray, 0, nullptr);
}

std::optional<ReflectionData>
findNearestHitPoint(const std::vector<std::unique_ptr<Shape>>& shapes, const Ray& incidentRay) {
    std::optional<ReflectionData> nearestReflection = std::nullopt;
    for (const auto& shape : shapes) {
        auto reflected = shape->intersects_with(incidentRay);
        if (reflected.has_value()) {
            if (!nearestReflection.has_value()) {
                nearestReflection = reflected;
            } else if (dist2(reflected->reflection.pos, incidentRay.pos) <
                       dist2(nearestReflection->reflection.pos, incidentRay.pos)) {
                nearestReflection = reflected;
            }
        }
    }
    return nearestReflection;
}


std::pair<const DrawableShape*, std::optional<ReflectionData>>
findNearestHitPoint(const std::vector<DrawableShape>& shapes, const Ray& incidentRay, const DrawableShape* pIgnoreShape) {
  const DrawableShape* pNearestDrawableShape = nullptr;
  std::optional<ReflectionData> nearestReflection = std::nullopt;
  for (const auto& drawableShape : shapes) {
    if (&drawableShape != pIgnoreShape) {
      auto reflected = drawableShape.shape->intersects_with(incidentRay);
      if (reflected.has_value()) {
        if (!nearestReflection.has_value()) {
          pNearestDrawableShape = &drawableShape;
          nearestReflection = reflected;
        }
        else if (dist2(reflected->reflection.pos, incidentRay.pos) < dist2(nearestReflection->reflection.pos, incidentRay.pos)) {
          pNearestDrawableShape = &drawableShape;
          nearestReflection = reflected;
        }
      }
    }
  }
  return std::make_pair(pNearestDrawableShape, nearestReflection);
}

Color traceShadowRay(const std::vector<DrawableShape>& shapes, const ReflectionData& orign, const Ray& fromEye, const DrawableShape* pIgnoreShape) {
  // find nearest shape
  const DrawableShape* pNearestShape = nullptr;
  float maxDist2 = 99999.f;
  for (const auto& drawableShape : shapes) {
    if (&drawableShape != pIgnoreShape) {
      if (auto ref = drawableShape.shape->intersects_with(orign.reflection); ref.has_value()) {
        vec shapeDir = ref->reflection.pos - orign.reflection.pos;
        float shapeDirMag2 = shapeDir.mag2();
        if (shapeDirMag2 < maxDist2) {
          maxDist2 = shapeDirMag2;
          pNearestShape = &drawableShape;
        }
      }
    }
  }

  // if the nearest object emits light, add some color
  Color final_color = BLACK;
  if (pNearestShape->properties.intensity > 0.f) {
    float diffuse_light_intensity = std::max(0.f, orign.norm.dot(orign.reflection.dir)) * pNearestShape->properties.intensity;
    const auto r = -reflect(-orign.reflection.dir, orign.norm);
    const auto rdotprim = std::max(0.f, r.dot(fromEye.dir));
    float specular_light_intensity = myPow(rdotprim, pNearestShape->properties.specular_exp) * pNearestShape->properties.intensity;
    final_color += pIgnoreShape->properties.color * pIgnoreShape->properties.diffuse_factor * diffuse_light_intensity +
      pNearestShape->properties.color * pIgnoreShape->properties.specular_factor * specular_light_intensity;
  }
  return final_color;
}

Color RayTracer::trace(const std::vector<DrawableShape>& shapes, const Ray& incidentRay, int depth, const DrawableShape* curShape) const {
  if (depth >= max_depth) { // recursive base case
    return BLACK;
  }

  auto [pNearestDrawableShape, nearestReflection] = findNearestHitPoint(shapes, incidentRay, curShape);

  // light it up
  Color final_color = BLACK;
  if (!nearestReflection.has_value()) {
    final_color = background_color;
  }
  else {
    final_color = pNearestDrawableShape->properties.color * pNearestDrawableShape->properties.intensity; // if shape is a light source
    if(auto tex = TextureManager::instance().getTexture(pNearestDrawableShape->properties.textureId); tex != nullptr) {
      final_color += tex->getColor(nearestReflection->u, nearestReflection->v) * ambient_light_intensity;
    }
    else {
      final_color += pNearestDrawableShape->properties.color * ambient_light_intensity;
    }
    Color reflected_color = trace(shapes, nearestReflection->reflection, depth + 1, pNearestDrawableShape);
    final_color += reflected_color * pNearestDrawableShape->properties.reflect_factor;

    // scan light sources to calculate diffuse and specular components
    for (auto& light_source : shapes) {
      if (&light_source != pNearestDrawableShape && light_source.properties.intensity > 0.0f) {
        vec lightDir = light_source.shape->getPos() - nearestReflection->reflection.pos;
        float lightMag2 = lightDir.mag2();
        lightDir.normalize();
        final_color += traceShadowRay(shapes, ReflectionData{ Ray{ nearestReflection->reflection.pos, lightDir }, nearestReflection->norm, 0.f, 0.f }, incidentRay, pNearestDrawableShape);
      }
    }
  }
  return final_color;
}

