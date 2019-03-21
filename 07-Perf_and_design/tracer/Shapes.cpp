#include <vector>
#include <functional>
#include "Shapes.h"


std::optional<ReflectionData> intersects(const Sphere& sphere, const Ray& incident_ray) {
  auto v_ray2sph_center = sphere.pos - incident_ray.pos;
  auto v_r2s_proj_ray = v_ray2sph_center.dot(incident_ray.dir); // projection of ray_origin_to_sphere onto ray
  if (v_r2s_proj_ray < 0.f) {  // if sphere is behind ray origin
    return std::nullopt;
  }
  auto v_ray2sph_bis = incident_ray.dir * v_r2s_proj_ray; // vector from ray origin to midway through the sphere along the ray
  auto v_min_dist = v_ray2sph_bis - v_ray2sph_center; // vector from sphere center to closest point on the ray 
  float d2 = v_min_dist.mag2();
  float r2 = sphere.radius*sphere.radius; 
  if (d2 > r2) { // if min distance between ray and sphere is greater than radius, then no intersection
    return std::nullopt;
  }
  float cd2 = r2 - d2; // ratio of v_ray2sph_bis that is inside the sphere... squared
  float ratio = 1.f - std::sqrtf(cd2) / v_ray2sph_bis.mag(); // the remaining portion of v_ray2sph_bis leads to the surface of the sphere
  auto v_ray2sph_surface = v_ray2sph_bis * ratio;
  auto p_sphere_surface = incident_ray.pos + v_ray2sph_surface; 
  auto v_norm = p_sphere_surface - sphere.pos;
  v_norm.normalize();
  auto v_reflection = reflect(incident_ray.dir, v_norm);
  return std::make_optional(ReflectionData(Ray(p_sphere_surface, v_reflection), v_norm));
}


std::optional<ReflectionData> barycentric_intersects(const vec & pos1, const vec& p2mp1, const vec& p3mp1, const vec& norm, const Ray & incident_ray, std::function<bool(float, float)> func)
{
  // use Cramers rule to solve for barycentric coordinates (alpha and gamma) and t in this equation
  // incident_ray.pos + incident_ray.dir * t = pos1 + alpha * (pos2 - pos1) + gamma * (pos3 - pos1);
  const auto& AmC = p2mp1;
  const auto& AmB = p3mp1;
  const auto& dir = incident_ray.dir;
  const float incident_dot_norm = -dir.dot(norm);
  // early abort if surface is facing away from the ray
  if (incident_dot_norm < 0.f) {
    return std::nullopt;
  }
  const auto AmP = pos1 - incident_ray.pos;
  // Determinates...  I really need to use a matrix class that has a det method`
  const float detA = AmB.x * (AmC.y*dir.z - dir.y*AmC.z) + AmC.x * (dir.y*AmB.z - AmB.y*dir.z) + dir.x * (AmB.y*AmC.z - AmC.y*AmB.z);
  const float tDet = AmB.x * (AmC.y*AmP.z - AmP.y*AmC.z) + AmC.x * (AmP.y*AmB.z - AmB.y*AmP.z) + AmP.x * (AmB.y*AmC.z - AmC.y*AmB.z);
  const float gamDet = AmB.x * (AmP.y*dir.z - dir.y*AmP.z) + AmP.x * (dir.y*AmB.z - AmB.y*dir.z) + dir.x * (AmB.y*AmP.z - AmP.y*AmB.z);
  const float betDet = AmP.x * (AmC.y*dir.z - dir.y*AmC.z) + AmC.x * (dir.y*AmP.z - AmP.y*dir.z) + dir.x * (AmP.y*AmC.z - AmC.y*AmP.z);
  const float overDetA = 1.0f / detA;
  const float beta = betDet * overDetA;
  const float gamma = gamDet * overDetA;
  const float t = tDet * overDetA;
  // intersection if barycentric coordinates between 0 and 1, and t is positive
  if(!func(beta, gamma) || t < 0.f) {
    return std::nullopt;
  }
  const auto hitPoint = incident_ray.pos + incident_ray.dir * t;
  auto reflection = reflect(incident_ray.dir, norm);
  return std::make_optional(ReflectionData(Ray(hitPoint, reflection), norm));
}

std::optional<ReflectionData> intersects(const Triangle & triangle, const Ray & incident_ray)
{
  return barycentric_intersects(triangle.pos, triangle.p2mp1, triangle.p3mp1, triangle.norm, incident_ray, [](float beta, float gamma) {
    return beta >= 0.f && gamma >= 0.f && beta + gamma <= 1.f;
  });
}

std::optional<ReflectionData> intersects(const Rect & rect, const Ray & incident_ray)
{
  return barycentric_intersects(rect.pos, rect.p2mp1, rect.p3mp1, rect.norm, incident_ray, [](float beta, float gamma) {
    return beta >= 0.f && gamma >= 0.f && beta <= 1.f && gamma <= 1.f;
  });
}

std::optional<ReflectionData> Sphere::intersects_with(const Ray & ray) const
{
  return intersects(*this, ray); 
}

std::optional<ReflectionData> Triangle::intersects_with(const Ray & ray) const
{
  return intersects(*this, ray); 
}

std::optional<ReflectionData> Rect::intersects_with(const Ray & ray) const
{
  return intersects(*this, ray); 
}
