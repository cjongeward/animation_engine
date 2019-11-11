#include <vector>
#include <functional>
#include "Shapes.h"
#include "MeshReader.h"
#include "RayTracer.h"


std::optional<ReflectionData> Sphere::intersects_with(const Ray &incident_ray) const {
    auto v_ray2sph_center = pos - incident_ray.pos;
    auto v_r2s_proj_ray = v_ray2sph_center.dot(incident_ray.dir); // projection of ray_origin_to_sphere onto ray
    if (v_r2s_proj_ray < 0.f) {  // if sphere is behind ray origin
        return std::nullopt;
    }
    auto v_ray2sph_bis =
            incident_ray.dir * v_r2s_proj_ray; // vector from ray origin to midway through the sphere along the ray
    auto v_min_dist = v_ray2sph_bis - v_ray2sph_center; // vector from sphere center to closest point on the ray
    float d2 = v_min_dist.mag2();
    float r2 = radius * radius;
    if (d2 > r2) { // if min distance between ray and sphere is greater than radius, then no intersection
        return std::nullopt;
    }
    float cd2 = r2 - d2; // ratio of v_ray2sph_bis that is inside the sphere... squared
    float ratio = 1.f - std::sqrt(cd2) /
                        v_ray2sph_bis.mag(); // the remaining portion of v_ray2sph_bis leads to the surface of the sphere
    auto v_ray2sph_surface = v_ray2sph_bis * ratio;
    auto p_sphere_surface = incident_ray.pos + v_ray2sph_surface;
    auto v_norm = p_sphere_surface - pos;
    v_norm.normalize();
    auto v_reflection = reflect(incident_ray.dir, v_norm);
    return std::make_optional(ReflectionData(Ray(p_sphere_surface, v_reflection), v_norm, 0.f, 0.f));
}

Sphere::Sphere(const vec &t_pos, float t_radius) :
        pos{t_pos},
        radius{t_radius}
        {}

void Sphere::transform(const mat &xfrom) {
    pos = xfrom * pos;
    radius *= xfrom.getMaxSizeEle();
}

template<class FUNC>
std::optional<ReflectionData>
barycentric_intersects(const vec &pos1, const vec &p2mp1, const vec &p3mp1, const vec &norm, const Ray &incident_ray,
                       FUNC func) {
    // use Cramers rule to solve for barycentric coordinates (alpha and gamma) and t in this equation
    // incident_ray.pos + incident_ray.dir * t = pos1 + alpha * (pos2 - pos1) + gamma * (pos3 - pos1);
    const auto &dir = incident_ray.dir;
    const float incident_dot_norm = -dir.dot(norm);
    // early abort if surface is facing away from the ray
    if (incident_dot_norm < 0.f) {
        return std::nullopt;
    }
    const auto AmP = pos1 - incident_ray.pos;
    // Determinates...  I really need to use a matrix class that has a det method`
    const float detA = p3mp1.x * (p2mp1.y * dir.z - dir.y * p2mp1.z) + p2mp1.x * (dir.y * p3mp1.z - p3mp1.y * dir.z) +
                       dir.x * (p3mp1.y * p2mp1.z - p2mp1.y * p3mp1.z);
    const float tDet = p3mp1.x * (p2mp1.y * AmP.z - AmP.y * p2mp1.z) + p2mp1.x * (AmP.y * p3mp1.z - p3mp1.y * AmP.z) +
                       AmP.x * (p3mp1.y * p2mp1.z - p2mp1.y * p3mp1.z);
    const float gamDet = p3mp1.x * (AmP.y * dir.z - dir.y * AmP.z) + AmP.x * (dir.y * p3mp1.z - p3mp1.y * dir.z) +
                         dir.x * (p3mp1.y * AmP.z - AmP.y * p3mp1.z);
    const float betDet = AmP.x * (p2mp1.y * dir.z - dir.y * p2mp1.z) + p2mp1.x * (dir.y * AmP.z - AmP.y * dir.z) +
                         dir.x * (AmP.y * p2mp1.z - p2mp1.y * AmP.z);
    const float overDetA = 1.0f / detA;
    const float beta = betDet * overDetA;
    const float gamma = gamDet * overDetA;
    const float t = tDet * overDetA;
    // intersection if barycentric coordinates between 0 and 1, and t is positive
    if (t < 0.f || !func(beta, gamma)) {
        return std::nullopt;
    }
    const auto hitPoint = incident_ray.pos + incident_ray.dir * t;
    auto reflection = reflect(incident_ray.dir, norm);
    return std::make_optional(ReflectionData(Ray(hitPoint, reflection), norm, beta, gamma));
}

std::optional<ReflectionData> Triangle::intersects_with(const Ray &incident_ray) const {
    return barycentric_intersects(pos, p2mp1, p3mp1, norm, incident_ray, [](float beta, float gamma) {
        return beta >= 0.f && gamma >= 0.f && beta + gamma <= 1.f;
    });
}

Triangle::Triangle(const vec &t_pos, const vec &t_pos2, const vec &t_pos3) :
        pos{t_pos},
        pos2{t_pos2},
        pos3{t_pos3},
        p2mp1{pos - pos2},
        p3mp1{pos - pos3},
        norm{-p3mp1.cross(p2mp1)}
{
    norm.normalize();
}

void Triangle::transform(const mat &xfrom) {
    pos = xfrom * pos;
    pos2 = xfrom * pos2;
    pos3 = xfrom * pos3;
    p2mp1 = pos - pos2;
    p3mp1 = pos - pos3;
    norm = -p3mp1.cross(p2mp1);
    norm.normalize();
}

std::optional<ReflectionData> Rect::intersects_with(const Ray &incident_ray) const {
    return barycentric_intersects(pos, p2mp1, p3mp1, norm, incident_ray, [](float beta, float gamma) {
        return beta >= 0.f && gamma >= 0.f && beta <= 1.f && gamma <= 1.f;
    });
}

Rect::Rect(const vec &t_pos, const vec &t_pos2, const vec &t_pos3) :
        pos{t_pos},
        pos2{t_pos2},
        pos3{t_pos3},
        p2mp1{pos - pos2},
        p3mp1{pos - pos3},
        norm{-p3mp1.cross(p2mp1)}
{
    norm.normalize();
}

void Rect::transform(const mat &xfrom) {
    pos = xfrom * pos;
    pos2 = xfrom * pos2;
    pos3 = xfrom * pos3;
    p2mp1 = pos - pos2;
    p3mp1 = pos - pos3;
    norm = -p3mp1.cross(p2mp1);
    norm.normalize();
}

static constexpr vec blf{-0.5f, -0.5f, -0.5f};
static constexpr vec blb{-0.5f, -0.5f, 0.5f};
static constexpr vec tlf{-0.5f, 0.5f, -0.5f};
static constexpr vec tlb{-0.5f, 0.5f, 0.5f};
static constexpr vec brf{0.5f, -0.5f, -0.5f};
static constexpr vec brb{0.5f, -0.5f, 0.5f};
static constexpr vec trf{0.5f, 0.5f, -0.5f};
static constexpr vec trb{0.5f, 0.5f, 0.5f};
auto makeBox() {
    std::vector<Rect> rectangles;
    rectangles.emplace_back(blb, brb, tlb);
    rectangles.emplace_back(brb, brf, trb);
    rectangles.emplace_back(brf, blf, trf);
    rectangles.emplace_back(blf, blb, tlf);
    rectangles.emplace_back(tlb, trb, tlf);
    rectangles.emplace_back(blf, brf, blb);
    return rectangles;
}

Box::Box() :
    rectangles{makeBox()},
    boundingSphere{vec{0.f, 0.f,0.f}, 1.8f}
{ }

std::optional<ReflectionData> Box::intersects_with(const Ray &ray) const {
    if(boundingSphere.intersects_with(ray)) {
        std::optional<ReflectionData> nearestReflection = std::nullopt;
        for (auto& rect : rectangles) {
            auto reflected = rect.intersects_with(ray);
            if (reflected.has_value()) {
                if (!nearestReflection.has_value()) {
                    nearestReflection = reflected;
                } else if (dist2(reflected->reflection.pos, ray.pos) < dist2(nearestReflection->reflection.pos, ray.pos)) {
                    nearestReflection = reflected;
                }
            }
        }
        return  nearestReflection;
    }
    return std::nullopt;
}

void Box::transform(const mat &xfrom) {
    for (auto &shape : rectangles) {
        shape.transform(xfrom);
    }
    boundingSphere.transform(xfrom);
}


Mesh::Mesh(const std::string& filename) :
    triangles(parseMesh(filename)),
    boundingSphere{vec{0.f, 0.f,0.f}, 1.f}
{
    boundingSphere.transform(mat::scale(vec{1.8f, 1.8f, 1.8f}));
}

std::optional<ReflectionData> Mesh::intersects_with(const Ray &ray) const {
    if(boundingSphere.intersects_with(ray)) {
        std::optional<ReflectionData> nearestReflection = std::nullopt;
        for (auto& tri : triangles) {
            auto reflected = tri.intersects_with(ray);
            if (reflected.has_value()) {
                if (!nearestReflection.has_value()) {
                    nearestReflection = reflected;
                } else if (dist2(reflected->reflection.pos, ray.pos) < dist2(nearestReflection->reflection.pos, ray.pos)) {
                    nearestReflection = reflected;
                }
            }
        }
        return  nearestReflection;
    }
    return std::nullopt;
}

void Mesh::transform(const mat &xfrom) {
    for (auto &shape : triangles) {
        shape.transform(xfrom);
    }
    boundingSphere.transform(xfrom);
}

