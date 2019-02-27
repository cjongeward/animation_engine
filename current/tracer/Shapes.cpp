#include "Shapes.h"

std::optional<ReflectionData> Sphere::intersectsWith(Ray incident) {
  return intersects(incident, *this);
}
std::optional<ReflectionData> Plane::intersectsWith(Ray incident) {
  return intersects(incident, *this);
}
std::optional<ReflectionData> AARect::intersectsWith(Ray incident) {
  return intersects(incident, *this);
}
vec reflection(const vec& orig, const vec& norm) {
  auto orig_dot_norm = orig.dot(norm);
  auto real_norm = norm;
  if (orig_dot_norm > 0) {
    real_norm = real_norm * -1.f;
  }
  return orig - real_norm * 2.f * orig.dot(real_norm);
}

std::optional<ReflectionData> intersects(Ray incident, Sphere s) {
  auto v_rayToSphere = s.pos - incident.pos;
  auto v_r2s_proj_ray = v_rayToSphere.dot(incident.dir); // projection of ray_origin_to_sphere onto ray
  if (v_r2s_proj_ray < 0.f) {  // if sphere is behind ray origin
    return std::nullopt;
  }
  auto v_d2sphere = incident.dir * v_r2s_proj_ray; // vector from ray origin to middle of sphere along the ray
  auto vms = v_d2sphere - v_rayToSphere; // vector rejection 
  float d2 = vms.mag2();
  float r2 = s.radius*s.radius; // radius squared
  if (d2 > r2) { // if rejection is greater than radius, then no intersection
    return std::nullopt;
  }
  float cd2 = r2 - d2; // pythagorean, calculate component along rayToSphere that is within the sphere 
  float ratio = 1.f - std::sqrtf(cd2) / v_d2sphere.mag(); // whatever is left is the vector from the ray origin to the ray intersection point
  auto vc = v_d2sphere * ratio;
  auto pc = incident.pos + vc;
  auto n = pc - s.pos;
  n.normalize();
  auto rhat = reflection(incident.dir, n);
  return std::make_optional(ReflectionData(Ray(pc, rhat), n));
}

std::optional<ReflectionData> intersects(Ray incident, Plane p) {
  auto ray_to_plane_vec = p.pos - incident.pos;
  auto ray_to_plane_proj = ray_to_plane_vec.dot(p.norm);
  auto ray_proj_to_norm = incident.dir.dot(p.norm);
  if (ray_proj_to_norm > -0.01f && ray_proj_to_norm < 0.01f) {
    return std::nullopt;
  }
  auto t = ray_to_plane_proj / ray_proj_to_norm;
  auto point = incident.pos + incident.dir * t;
  auto norm = p.norm;
  if (norm.dot(incident.dir) > 0.f) {
    norm = norm * -1.f;
  }
  auto reflectedVec = reflection(incident.dir, norm);
  return std::make_optional(ReflectionData{ Ray{point, reflectedVec}, norm });
}

std::optional<ReflectionData> intersects(Ray incident, AARect r) {
  if (r.size.x == 0.f) {
    auto t = (r.pos.x - incident.pos.x) / incident.dir.x;
    auto p = incident.pos + incident.dir * t;
    if (t > 0.f && p.y >= r.pos.y && p.y <= r.pos.y + r.size.y && p.z >= r.pos.z && p.z <= r.pos.z + r.size.z) {
      vec norm{ 1.f, 0.f, 0.f };
      if (incident.dir.dot(norm) > 0) {
        norm *= -1.f;
      }
      vec refl = reflection(incident.dir, norm);
      return std::make_optional(ReflectionData{ Ray{p, refl}, norm });
    }
  }
  else if (r.size.y == 0.f) {
    auto t = (r.pos.y - incident.pos.y) / incident.dir.y;
    auto p = incident.pos + incident.dir * t;
    if (t > 0.f && p.x >= r.pos.x && p.x <= r.pos.x + r.size.x && p.z >= r.pos.z && p.z <= r.pos.z + r.size.z) {
      vec norm{ 0.f, 1.f, 0.f };
      if (incident.dir.dot(norm) > 0) {
        norm *= -1.f;
      }
      vec refl = reflection(incident.dir, norm);
      return std::make_optional(ReflectionData{ Ray{p, refl}, norm });
    }
  }
  else if (r.size.z == 0.f) {
    auto t = (r.pos.z - incident.pos.z) / incident.dir.z;
    auto p = incident.pos + incident.dir * t;
    if (t > 0.f && p.x >= r.pos.x && p.x <= r.pos.x + r.size.x && p.y >= r.pos.y && p.y <= r.pos.y + r.size.y) {
      vec norm{ 0.f, 0.f, 1.f };
      if (incident.dir.dot(norm) > 0) {
        norm *= -1.f;
      }
      vec refl = reflection(incident.dir, norm);
      return std::make_optional(ReflectionData{ Ray{p, refl}, norm });
    }
  }


  return std::nullopt;
}


