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

Color RayTracer::trace(const Scene& scene) const {
  return trace(scene, primary_ray, 0, NullShapeID);
}

Color traceShadowRay(const Scene& scene, const ReflectionData& orign, const Ray& fromEye, const ShapeID& curShape) {

  auto nearestHit = scene.findNearestHitPoint(orign.reflection, curShape);
  auto hitProperties = scene.getProperties(nearestHit->first);
  auto curProperties = scene.getProperties(curShape);

  // if the nearest object emits light, add some color
  Color final_color = BLACK;
  if (hitProperties.intensity > 0.f) {
    float diffuse_light_intensity = std::max(0.f, orign.norm.dot(orign.reflection.dir)) * hitProperties.intensity;
    const auto r = -reflect(-orign.reflection.dir, orign.norm);
    const auto rdotprim = std::max(0.f, r.dot(fromEye.dir));
    float specular_light_intensity = myPow(rdotprim, hitProperties.specular_exp) * hitProperties.intensity;
    final_color += curProperties.color * curProperties.diffuse_factor * diffuse_light_intensity +
      curProperties.color * curProperties.specular_factor * specular_light_intensity;
  }
  return final_color;
}

Color getEmittedLight( const SurfaceProperties& surfaceProperties) {
    return surfaceProperties.color * surfaceProperties.intensity;
}

Color getAmbientColor(const SurfaceProperties& surfaceProperties, const ReflectionData& nearestReflection, float ambient_light_intensity) {
    if(auto tex = TextureManager::instance().getTexture(surfaceProperties.textureId); tex != nullptr) {
        return tex->getColor(nearestReflection.u, nearestReflection.v) * ambient_light_intensity;
    }
    return surfaceProperties.color * ambient_light_intensity;
}

Color lightItUp(const Scene& scene, const ShapeID& curShape, const ReflectionData& nearestReflection, const Ray& incidentRay) {
    // scan light sources to calculate diffuse and specular components
    Color final_color = BLACK;
    for (int i = 0; i < scene.lights.size(); ++i) {
        ShapeID lightid{ShapeTables::LIGHTS, i};
        auto lightProperties = scene.getProperties(lightid);
        if (lightid != curShape && lightProperties.intensity > 0.0f) {
            vec lightDir = scene.lights[i].getPos() - nearestReflection.reflection.pos;
            float lightMag2 = lightDir.mag2();
            lightDir.normalize();
            final_color += traceShadowRay(scene, ReflectionData{ Ray{ nearestReflection.reflection.pos, lightDir }, nearestReflection.norm, 0.f, 0.f }, incidentRay, curShape);
        }
    }
    return final_color;
}

Color RayTracer::trace(const Scene& scene, const Ray& incidentRay, int depth, const ShapeID& curShape) const {
  if (depth >= max_depth) { // base case
    return BLACK;
  }

  auto nearestReflection = scene.findNearestHitPoint(incidentRay, curShape);

  Color final_color = BLACK;
  if (!nearestReflection.has_value()) {
    final_color = background_color;
  }
  else {
      auto surfaceProperties = scene.getProperties(nearestReflection->first);
//      final_color = getEmittedLight(surfaceProperties);
      final_color += getAmbientColor(surfaceProperties, nearestReflection->second, ambient_light_intensity);
//      if(surfaceProperties.reflect_factor > 0.f) {
//          final_color += trace(scene, nearestReflection->second.reflection, depth + 1, nearestReflection->first) * surfaceProperties.reflect_factor;
//      }
//      final_color += lightItUp(scene, nearestReflection->first, nearestReflection->second, incidentRay);
  }

  return final_color;
}


