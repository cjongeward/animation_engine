#include "Scene.h"
#include "Settings.h"

Scene::Scene() {
    Sphere sphere{vec{0.f, -3.f, -4.f}, 1.f};
    spheres.push_back(sphere);
    spheres_properties.push_back(MIRRORISH);
    Sphere sphere2{vec{7.5f, -3.f, -15.f}, 1.f};
    spheres.push_back(sphere2);
    spheres_properties.push_back(BRIGHT);
    Sphere sphere3{vec{1.5f, -3.f, -13.f}, 1.f};
    spheres.push_back(sphere3);
    spheres_properties.push_back(REDISH);
    Sphere sphere4{vec{3.5f, -3.f, -7.f}, 1.f};
    spheres.push_back(sphere4);
    spheres_properties.push_back(DULL);
    Sphere sphere5{vec{6.5f, -3.f, -7.f}, 1.f};
    spheres.push_back(sphere5);
    spheres_properties.push_back(BRIGHT);
    Sphere light_bulb{vec{-2.f, 3.95f, -6.f}, 0.25f};
    lights.push_back(light_bulb);
    lights_properties.push_back(LIGHT);
    Sphere light_bulb2{vec{2.f, 3.95f, -6.f}, 0.25f};
    lights.push_back(light_bulb2);
    lights_properties.push_back(LIGHT);
    Sphere sun{vec{200.f, 80.f, 60.f}, 0.25f};
    lights.push_back(sun);
    lights_properties.push_back(SUN);


    Box box1;
    box1.transform(mat::translation(vec{-7.f, -3.f, -12.f}) * mat::scale(vec{2.f, 2.f, 2.f}));
    boxes.push_back(box1);
    boxes_properties.push_back(BRIGHT);
    Box win1;
    win1.transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 4.f, 0.15f}));
    boxes.push_back(win1);
    boxes_properties.push_back(BLACKISH);
    Box win2;
    win2.transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 0.15f, 4.f}));
    boxes.push_back(win2);
    boxes_properties.push_back(BLACKISH);
    Box plank;
    plank.transform(mat::translation(vec{9.5f, -0.5f, -3.f}) * mat::scale(vec{1.0f, 0.15f, 6.f}));
    boxes.push_back(plank);
    boxes_properties.push_back(BROWNISH);
    Box box2;
    box2.transform( mat::translation(vec{-1.f, -3.f, -6.f}) * mat::rotation(PI4, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));
    boxes.push_back(box2);
    boxes_properties.push_back(WHITEISH);
    Box box3;
    box3.transform( mat::translation(vec{2.f, -3.f, -9.f}) * mat::rotation(PI4, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));
    boxes.push_back(box3);
    boxes_properties.push_back(WHITEISH);
    Box plank2;
    plank2.transform(mat::translation(vec{0.5f, -1.93, -7.5f}) * mat::rotation(-PI4, 0.f, 0.f) * mat::scale(vec{1.0f, 0.15f, 6.f}));
    boxes.push_back(plank2);
    boxes_properties.push_back(BROWNISH);

    Rect grass{vec{10.f, -4.f, -40.f}, vec{10.f, -4.f, 20.f}, vec{30.f, -4.f, -40.f}};
    rects.push_back(grass);
    rects_properties.push_back(GRASS);
    Rect floor{vec{-10.f, -4.f, -20.f}, vec{-10.f, -4.f, 0.1f}, vec{10.f, -4.f, -20.f}};
    rects.push_back(floor);
    rects_properties.push_back(FLOOR);
    Rect wall1{vec{-10.f, -4.f, -20.f}, vec{-10.f, 4.f, -20.f}, vec{-10.f, -4.f, 0.f}};
    rects.push_back(wall1);
    rects_properties.push_back(YELLOWISH);
    Rect wall2a{vec{10.f, -4.f, 0.f}, vec{10.f, 4.f, 0.f}, vec{10.f, -4.f, -8.f}};
    rects.push_back(wall2a);
    rects_properties.push_back(YELLOWISH);
    Rect wall2aa{vec{10.f, -4.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.5f, -4.f, -8.f}};
    rects.push_back(wall2aa);
    rects_properties.push_back(YELLOWISH);
    Rect wall2b{vec{10.f, -4.f, -12.f}, vec{10.f, 4.f, -12.f}, vec{10.f, -4.f, -20.f}};
    rects.push_back(wall2b);
    rects_properties.push_back(YELLOWISH);
    Rect wall2bb{ vec{10.5f, -4.f, -12.f}, vec{10.5f, 4.f, -12.f}, vec{10.f, -4.f, -12.f}};
    rects.push_back(wall2bb);
    rects_properties.push_back(YELLOWISH);
    Rect wall2c{vec{10.f, 2.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.f, 2.f, -12.f}};
    rects.push_back(wall2c);
    rects_properties.push_back(YELLOWISH);
    Rect wall2cc{vec{10.5f, 2.f, -12.f}, vec{10.5f, 2.f, -8.f}, vec{10.f, 2.f, -12.f}};
    rects.push_back(wall2cc);
    rects_properties.push_back(YELLOWISH);
    Rect wall2d{vec{10.f, -4.f, -8.f}, vec{10.f, -2.f, -8.f}, vec{10.f, -4.f, -12.f}};
    rects.push_back(wall2d);
    rects_properties.push_back(YELLOWISH);
    Rect wall2dd{ vec{10.5f, -2.f, -8.f}, vec{10.5f, -2.f, -12.f}, vec{10.f, -2.f, -8.f}};
    rects.push_back(wall2dd);
    rects_properties.push_back(YELLOWISH);
    Rect wall3{vec{10.f, -4.f, -20.f}, vec{10.f, 4.f, -20.f}, vec{-10.f, -4.f, -20.f}};
    rects.push_back(wall3);
    rects_properties.push_back(YELLOWISH);
    Rect wall4{vec{-10.f, -4.f, 0.f}, vec{-10.f, 4.f, 0.f}, vec{10.f, -4.f, 0.f}};
    rects.push_back(wall4);
    rects_properties.push_back(YELLOWISH);
    Rect cieling{vec{-10.f, 4.f, -20.f}, vec{10.f, 4.f, -20.f}, vec{-10.f, 4.f, 0.1f}};
    rects.push_back(cieling);
    rects_properties.push_back(WHITEISH);
    Rect mirror{vec{5.f, -3.f, -19.9f}, vec{5.f, 3.f, -19.9f}, vec{-5.f, -3.f, -19.9f}};
    rects.push_back(mirror);
    rects_properties.push_back(MIRRORISH);
    Rect pic3{vec{9.9f, 0.f, -15.f}, vec{9.9f, 3.f, -15.f}, vec{9.9f, 0.f, -19.f}};
    rects.push_back(pic3);
    rects_properties.push_back(PIC3);
    Rect pic2{vec{9.9f, 0.f, -1.0f}, vec{9.9f, 3.f, -1.0f}, vec{9.9f, 0.f, -5.0f}};
    rects.push_back(pic2);
    rects_properties.push_back(PIC2);
    Rect pic1{vec{9.f, -1.f, -19.9f}, vec{9.f, 3.f, -19.9f}, vec{6.f, -1.f, -19.9f}};
    rects.push_back(pic1);
    rects_properties.push_back(PIC1);

    Mesh bunny{"../bunny.off"};
    bunny.transform(mat::translation(vec{-7.f, -1.0f, -12.f}) * mat::scale(vec{1.f, 1.f, 1.f}));
    meshes.push_back(bunny);
    meshes_properties.push_back(WHITEISH);

    Mesh bunny2{"../bunny.off"};
    bunny2.transform(mat::translation(vec{0.5f, -0.85, -7.5f}) * mat::scale(vec{1.f, 1.f, 1.f}));
    meshes.push_back(bunny2);
    meshes_properties.push_back(MIRRORISH);
}

void Scene::transform(const mat &xform) {
    auto transform_list = [](auto& list, const mat& xform){
        for(auto& shape : list) {
            shape.transform(xform);
        }
    };
    transform_list(lights, xform);
    transform_list(spheres, xform);
    transform_list(rects, xform);
    transform_list(boxes, xform);
    transform_list(meshes, xform);
}

std::optional<std::pair<ShapeID, ReflectionData>> Scene::findNearestHitPoint(const Ray &incidentRay) const {
    return findNearestHitPoint(incidentRay, NullShapeID);
}

template <typename T>
T nearest(const T& a, const T& b, const Ray& incidentRay) {
    if(!a && !b) {
        return static_cast<T>(std::nullopt);
    }
    if(a && !b) {
        return a;
    }
    if(b && !a) {
        return b;
    }
    if(dist2(a->second.reflection.pos, incidentRay.pos) < dist2(b->second.reflection.pos, incidentRay.pos)) {
        return a;
    }
    return b;
}

template <typename T>
std::optional<std::pair<ShapeID, ReflectionData>> tFindNearestHitPoint(const std::vector<T>& shapes, ShapeTables table, const Ray &incidentRay, const ShapeID &ignoreShape) {
    std::optional<std::pair<ShapeID, ReflectionData>> nearestShape = std::nullopt;
    for (int i = 0; i < shapes.size(); ++i) {
        ShapeID shapeid{table, i};
        if (shapeid != ignoreShape) {
            auto reflected = shapes[i].intersects_with(incidentRay);
            if (reflected.has_value()) {
                if (!nearestShape.has_value()) {
                    nearestShape = std::make_optional(std::make_pair(shapeid, reflected.value()));
                }
                else if (dist2(reflected->reflection.pos, incidentRay.pos) < dist2(nearestShape->second.reflection.pos, incidentRay.pos)) {
                    nearestShape = std::make_pair(shapeid, reflected.value());
                }
            }
        }
    }
    return nearestShape;
}

std::optional<std::pair<ShapeID, ReflectionData>> Scene::findNearestHitPoint(const Ray &incidentRay, const ShapeID &ignoreShape) const {
    auto nearestHitPoint = tFindNearestHitPoint(spheres, ShapeTables::SPHERES, incidentRay, ignoreShape);
    nearestHitPoint = nearest(nearestHitPoint, tFindNearestHitPoint(lights, ShapeTables::LIGHTS, incidentRay, ignoreShape), incidentRay);
    nearestHitPoint = nearest(nearestHitPoint, tFindNearestHitPoint(rects, ShapeTables::RECTS, incidentRay, ignoreShape), incidentRay);
    nearestHitPoint = nearest(nearestHitPoint, tFindNearestHitPoint(boxes, ShapeTables::BOXES, incidentRay, ignoreShape), incidentRay);
    nearestHitPoint = nearest(nearestHitPoint, tFindNearestHitPoint(meshes, ShapeTables::MESHES, incidentRay, ignoreShape), incidentRay);
    return nearestHitPoint;
}
