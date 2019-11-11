#ifndef SHAPES_H_
#define SHAPES_H_

#include <optional>
#include "vec.h"
#include "Reflection.h"

// data packet containing important data from a reflection
struct ReflectionData {
    Ray reflection;
    vec norm;
    float u = 0.f;
    float v = 0.f;

    ReflectionData(const Ray &t_reflection, const vec &t_norm, float t_u, float t_v) : reflection{t_reflection},
                                                                                       norm{t_norm}, u{t_u}, v{t_v} {}
};

class Sphere {
private:
    vec pos;
    float radius;

public:
    Sphere(const vec &t_pos, float t_radius);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const ;
    void transform(const mat &xfrom) ;

    const vec &getPos() const {
        return pos;
    }

};

class Triangle {
private:
    vec pos;
    vec pos2;
    vec pos3;
    vec p2mp1;
    vec p3mp1;
    vec norm;

public:
    Triangle(const vec &t_pos, const vec &t_pos2, const vec &t_pos3);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const ;
    void transform(const mat &xfrom) ;

    const vec &getPos() const {
        return pos;
    }
};

struct Rect {
private:
    vec pos;
    vec pos2;
    vec pos3;
    vec p2mp1;
    vec p3mp1;
    vec norm;

public:
    Rect(const vec &t_pos, const vec &t_pos2, const vec &t_pos3);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const ;
    void transform(const mat &xfrom) ;

    const vec &getPos() const {
        return pos;
    }
};

class Box {
private:
    Sphere boundingSphere;
    std::vector<Rect> rectangles;

public:
    Box();
    std::optional<ReflectionData> intersects_with(const Ray &ray) const;
    void transform(const mat &xfrom) ;

    const vec &getPos() const {
        return rectangles.front().getPos();
    }
};

class Mesh {
private:
    Sphere boundingSphere;
    std::vector<Triangle> triangles;

public:
    explicit Mesh(const std::string &filename);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const;
    void transform(const mat &xfrom) ;

    const vec &getPos() const {
        return triangles.front().getPos();
    }
};

#endif
