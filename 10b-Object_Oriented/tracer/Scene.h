#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include "Shapes.h"
#include "SurfaceProperties.h"

enum class ShapeTables {
    LIGHTS,
    SPHERES,
    RECTS,
    BOXES,
    MESHES
};

struct ShapeID {
    ShapeTables table;
    int index;
    constexpr ShapeID(ShapeTables t_table, int t_index) : table{t_table}, index{t_index} {}
    constexpr bool operator!=(const ShapeID& rhs) { return table != rhs.table || index != rhs.index; }
};
constexpr ShapeID NullShapeID{ShapeTables::MESHES, -1};

class Scene {
public:
    std::vector<Sphere> lights;
    std::vector<Sphere> spheres;
    std::vector<Rect> rects;
    std::vector<Box> boxes;
    std::vector<Mesh> meshes;

    std::vector<SurfaceProperties> lights_properties;
    std::vector<SurfaceProperties> spheres_properties;
    std::vector<SurfaceProperties> rects_properties;
    std::vector<SurfaceProperties> boxes_properties;
    std::vector<SurfaceProperties> meshes_properties;

    Scene();
    void transform(const mat& xform);
    std::optional<std::pair<ShapeID, ReflectionData>> findNearestHitPoint(const Ray& incidentRay) const;
    std::optional<std::pair<ShapeID, ReflectionData>> findNearestHitPoint(const Ray& incidentRay, const ShapeID& ingnoreShape) const;

    SurfaceProperties getProperties(const ShapeID& id) const {
        switch(id.table){
            case ShapeTables::LIGHTS:
                return lights_properties[id.index];
            case ShapeTables::SPHERES:
                return spheres_properties[id.index];
            case ShapeTables::RECTS:
                return rects_properties[id.index];
            case ShapeTables::BOXES:
                return boxes_properties[id.index];
            case ShapeTables::MESHES:
                return meshes_properties[id.index];
        }
    }
};

#endif
