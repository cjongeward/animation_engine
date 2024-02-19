#include "RayTracer.h"
#include <optional>

float myPow(float val, int exp) {
  int curexp = 1;
  float curval = val;
  while (curexp < exp) {
    curval *= curval;
    curexp *= 2;
  }
  return curval;
}

Color RayTracer::trace(const std::unique_ptr<Shape>& rootShape) const {
  return trace(rootShape, primary_ray, 0, nullptr);
}

Color traceShadowRay(const std::unique_ptr<Shape>& shape, const HitData& orign, const Ray& fromEye, const Shape* pIgnoreShape) {
  // find nearest shape
  Color final_color = BLACK;
  if (auto nearestHit = shape->findNearestHitPoint(orign.reflection, pIgnoreShape); nearestHit.hitInfo.has_value()) {
    Shape* pNearestShape = nearestHit.hitShape;
    //  float maxDist2 = 99999.f;
    //  for (const auto& shape_up2 : shapes) {
    //    if (shape_up2.get() != pIgnoreShape) {
    //      Shape* pShape2 = shape_up2.get();
    //      if (auto ref = pShape2->intersects_with(orign.reflection); ref.has_value()) {
    //        vec shapeDir = ref->reflection.pos - orign.reflection.pos;
    //        float shapeDirMag2 = shapeDir.mag2();
    //        if (shapeDirMag2 < maxDist2) {
    //          maxDist2 = shapeDirMag2;
    //          pNearestShape = shape_up2.get();
    //        }
    //      }
    //    }
    //  }

      // if the nearest object emits light, add some color
    if (pNearestShape->properties.intensity > 0.f) {
      float diffuse_light_intensity = std::max(0.f, orign.norm.dot(orign.reflection.dir)) * pNearestShape->properties.intensity;
      const auto r = -reflect(-orign.reflection.dir, orign.norm);
      const auto rdotprim = std::max(0.f, r.dot(fromEye.dir));
      float specular_light_intensity = myPow(rdotprim, pNearestShape->properties.specular_exp) * pNearestShape->properties.intensity;
      final_color += pIgnoreShape->properties.color * pIgnoreShape->properties.diffuse_factor * diffuse_light_intensity +
        pNearestShape->properties.color * pIgnoreShape->properties.specular_factor * specular_light_intensity;
    }
  }
  return final_color;
}

Color RayTracer::trace(const std::unique_ptr<Shape>& shape, const Ray& incidentRay, int depth, const Shape* curShape) const {
  if (depth >= max_depth) { // recursive base case
    return BLACK;
  }

  auto RayTraceData = shape->findNearestHitPoint(incidentRay, curShape);

  // light it up
  Color final_color = BLACK;
  if (!RayTraceData.hitInfo.has_value()) {
    final_color = background_color;
  }
  else if (RayTraceData.hitShape->properties.intensity > 0.f) {
    final_color = RayTraceData.hitShape->properties.color;
  }
  else {
    if (auto tex = TextureManager::instance().getTexture(RayTraceData.hitShape->properties.textureId); tex != nullptr) {
      final_color += tex->getColor(RayTraceData.hitInfo->u, RayTraceData.hitInfo->v) * ambient_light_intensity;
    }
//    else if (auto& normalMap = RayTraceData.hitShape->properties.normalMap; normalMap.has_value()) {

 //   }
    else {
      final_color += RayTraceData.hitShape->properties.color * ambient_light_intensity;
    }
    Color reflected_color = trace(shape, RayTraceData.hitInfo->reflection, depth + 1, RayTraceData.hitShape);
    final_color += reflected_color * RayTraceData.hitShape->properties.reflect_factor;

    // scan light sources to calculate diffuse and specular components
    for (auto lightSources = shape->getLightSources(); auto lightSource : lightSources) {
      if (lightSource != RayTraceData.hitShape) {
        vec lightDir = lightSource->pos - RayTraceData.hitInfo->reflection.pos;
        float lightMag2 = lightDir.mag2();
        lightDir.normalize();
        final_color += traceShadowRay(shape, HitData{ Ray{ RayTraceData.hitInfo->reflection.pos, lightDir }, RayTraceData.hitInfo->norm, 0.f, 0.f }, incidentRay, RayTraceData.hitShape);
      }
    }

    for(auto& lightSource : RayTraceData.lightSources) {
      final_color += lightSource.color * lightSource.halo_factor;
    }

  }
  return final_color;
}

