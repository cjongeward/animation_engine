#ifndef SHAPES_H_
#define SHAPES_H_

#include <optional>
#include <memory>
#include "vec.h"
#include "SurfaceProperties.h"
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

class Shape {
public:
    SurfaceProperties properties;

    explicit Shape(const SurfaceProperties &t_properties) : properties{t_properties} {}

    virtual std::optional<ReflectionData> intersects_with(const Ray &ray) const = 0;
    virtual void transform(const mat &xform) = 0;
    virtual const vec &getPos() const = 0;
};

class DrawableShape {
private:
    std::unique_ptr<Shape> shape;
    SurfaceProperties properties;
};

class Sphere : public Shape {
private:
    vec pos;
    float radius;

public:
    Sphere(const vec &t_pos, const SurfaceProperties &t_properties, float t_radius);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const override;
    void transform(const mat &xfrom) override;

    const vec &getPos() const override {
        return pos;
    }

};

class Triangle : public Shape {
private:
    vec pos;
    vec pos2;
    vec pos3;
    vec p2mp1;
    vec p3mp1;
    vec norm;

public:
    Triangle(const vec &t_pos, const vec &t_pos2, const vec &t_pos3, const SurfaceProperties &t_properties);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const override;
    void transform(const mat &xfrom) override;

    const vec &getPos() const override {
        return pos;
    }
};

struct Rect : public Shape {
private:
    vec pos;
    vec pos2;
    vec pos3;
    vec p2mp1;
    vec p3mp1;
    vec norm;

public:
    Rect(const vec &t_pos, const vec &t_pos2, const vec &t_pos3, const SurfaceProperties &t_properties);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const override;
    void transform(const mat &xfrom) override;

    const vec &getPos() const override {
        return pos;
    }
};

class CompositeShape : public Shape {
public:
    std::vector<std::unique_ptr<Shape>> shapes;

    explicit CompositeShape(std::vector<std::unique_ptr<Shape>> t_shapes, const SurfaceProperties &t_properties);
    std::optional<ReflectionData> intersects_with(const Ray &ray) const final;
    void transform(const mat &xfrom) final;

    virtual Shape *getBoundingShape() = 0;
    virtual const Shape *getBoundingShape() const = 0;

    const vec &getPos() const override {
        return shapes.front()->getPos();
    }
};

class Box : public CompositeShape {
private:
    std::unique_ptr<Shape> boundingShape;

public:
    explicit Box(const SurfaceProperties &t_properties);
    Shape *getBoundingShape() override;
    const Shape *getBoundingShape() const override;
};

class Mesh : public CompositeShape {
private:
    std::unique_ptr<Shape> boundingShape;

public:
    Mesh(const std::string &filename, const SurfaceProperties &t_properties);
    Shape *getBoundingShape() override;
    const Shape *getBoundingShape() const override;
};

#endif
