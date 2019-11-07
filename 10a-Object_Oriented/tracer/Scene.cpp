#include "Scene.h"
#include "Settings.h"

std::vector<DrawableShape> Scene::getFrame() {
    // Assembles a room with a bunch of crap in it
    DrawableShape sphere{std::make_unique<Sphere>(vec{0.f, -3.f, -4.f}, 1.f), MIRRORISH};
    DrawableShape sphere2{std::make_unique<Sphere>(vec{7.5f, -3.f, -15.f}, 1.f), BRIGHT};
    DrawableShape sphere3{std::make_unique<Sphere>(vec{1.5f, -3.f, -13.f}, 1.f), REDISH};
    DrawableShape sphere4{std::make_unique<Sphere>(vec{3.5f, -3.f, -7.f}, 1.f), DULL};
    DrawableShape sphere5{std::make_unique<Sphere>(vec{6.5f, -3.f, -7.f}, 1.f), BRIGHT};
    DrawableShape light_bulb{std::make_unique<Sphere>(vec{-2.f, 3.95f, -6.f}, 0.25f), LIGHT};
    DrawableShape light_bulb2{std::make_unique<Sphere>(vec{2.f, 3.95f, -6.f}, 0.25f), LIGHT};
    DrawableShape sun{std::make_unique<Sphere>(vec{200.f, 80.f, 60.f}, 0.25f), SUN};

    DrawableShape box1{std::make_unique<Box>(), BRIGHT};
    box1.shape->transform(mat::translation(vec{-7.f, -3.f, -12.f}) * mat::scale(vec{2.f, 2.f, 2.f}));

    DrawableShape win1{std::make_unique<Box>(), BLACKISH};
    win1.shape->transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 4.f, 0.15f}));
    DrawableShape win2{std::make_unique<Box>(), BLACKISH};
    win2.shape->transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 0.15f, 4.f}));

    DrawableShape plank{std::make_unique<Box>(), BROWNISH};
    plank.shape->transform(mat::translation(vec{9.5f, -0.5f, -3.f}) * mat::scale(vec{1.0f, 0.15f, 6.f}));

    DrawableShape box2{std::make_unique<Box>(), WHITEISH};
    box2.shape->transform( mat::translation(vec{-1.f, -3.f, -6.f}) * mat::rotation(PI4, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));
    DrawableShape box3{std::make_unique<Box>(), WHITEISH};
    box3.shape->transform( mat::translation(vec{2.f, -3.f, -9.f}) * mat::rotation(PI4, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));
    DrawableShape plank2{std::make_unique<Box>(), BROWNISH};
    plank2.shape->transform(mat::translation(vec{0.5f, -1.93, -7.5f}) * mat::rotation(-PI4, 0.f, 0.f) * mat::scale(vec{1.0f, 0.15f, 6.f}));

    DrawableShape grass{std::make_unique<Rect>(vec{10.f, -4.f, -40.f}, vec{10.f, -4.f, 20.f}, vec{30.f, -4.f, -40.f}), GRASS};
    DrawableShape floor{std::make_unique<Rect>(vec{-10.f, -4.f, -20.f}, vec{-10.f, -4.f, 0.1f}, vec{10.f, -4.f, -20.f}), FLOOR};
    DrawableShape wall1{std::make_unique<Rect>(vec{-10.f, -4.f, -20.f}, vec{-10.f, 4.f, -20.f}, vec{-10.f, -4.f, 0.f}), YELLOWISH};
    DrawableShape wall2a{std::make_unique<Rect>(vec{10.f, -4.f, 0.f}, vec{10.f, 4.f, 0.f}, vec{10.f, -4.f, -8.f}), YELLOWISH};
    DrawableShape wall2aa{std::make_unique<Rect>(vec{10.f, -4.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.5f, -4.f, -8.f}), YELLOWISH};
    DrawableShape wall2b{std::make_unique<Rect>(vec{10.f, -4.f, -12.f}, vec{10.f, 4.f, -12.f}, vec{10.f, -4.f, -20.f}), YELLOWISH};
    DrawableShape wall2bb{ std::make_unique<Rect>(vec{10.5f, -4.f, -12.f}, vec{10.5f, 4.f, -12.f}, vec{10.f, -4.f, -12.f}), YELLOWISH};
    DrawableShape wall2c{std::make_unique<Rect>(vec{10.f, 2.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.f, 2.f, -12.f}), YELLOWISH};
    DrawableShape wall2cc{std::make_unique<Rect>(vec{10.5f, 2.f, -12.f}, vec{10.5f, 2.f, -8.f}, vec{10.f, 2.f, -12.f}), YELLOWISH};
    DrawableShape wall2d{std::make_unique<Rect>(vec{10.f, -4.f, -8.f}, vec{10.f, -2.f, -8.f}, vec{10.f, -4.f, -12.f}), YELLOWISH};
    DrawableShape wall2dd{ std::make_unique<Rect>(vec{10.5f, -2.f, -8.f}, vec{10.5f, -2.f, -12.f}, vec{10.f, -2.f, -8.f}), YELLOWISH};
    DrawableShape wall3{std::make_unique<Rect>(vec{10.f, -4.f, -20.f}, vec{10.f, 4.f, -20.f}, vec{-10.f, -4.f, -20.f}), YELLOWISH};
    DrawableShape wall4{std::make_unique<Rect>(vec{-10.f, -4.f, 0.f}, vec{-10.f, 4.f, 0.f}, vec{10.f, -4.f, 0.f}), YELLOWISH};
    DrawableShape cieling{std::make_unique<Rect>(vec{-10.f, 4.f, -20.f}, vec{10.f, 4.f, -20.f}, vec{-10.f, 4.f, 0.1f}), WHITEISH};
    DrawableShape mirror{std::make_unique<Rect>(vec{5.f, -3.f, -19.9f}, vec{5.f, 3.f, -19.9f}, vec{-5.f, -3.f, -19.9f}), MIRRORISH};
    DrawableShape pic3{std::make_unique<Rect>(vec{9.9f, 0.f, -15.f}, vec{9.9f, 3.f, -15.f}, vec{9.9f, 0.f, -19.f}), PIC3};
    DrawableShape pic2{std::make_unique<Rect>(vec{9.9f, 0.f, -1.0f}, vec{9.9f, 3.f, -1.0f}, vec{9.9f, 0.f, -5.0f}), PIC2};
    DrawableShape pic1{std::make_unique<Rect>(vec{9.f, -1.f, -19.9f}, vec{9.f, 3.f, -19.9f}, vec{6.f, -1.f, -19.9f}), PIC1};

    DrawableShape bunny{std::make_unique<Mesh>("../bunny.off"), WHITEISH};
    bunny.shape->transform(mat::translation(vec{-7.f, -1.0f, -12.f}) * mat::scale(vec{1.f, 1.f, 1.f}));

    DrawableShape bunny2{std::make_unique<Mesh>("../bunny.off"), MIRRORISH};
    bunny2.shape->transform(mat::translation(vec{0.5f, -0.85, -7.5f}) * mat::scale(vec{1.f, 1.f, 1.f}));

    std::vector<DrawableShape> shapes;
    shapes.push_back(std::move(sphere));
    shapes.push_back(std::move(sphere2));
    shapes.push_back(std::move(sphere3));
    shapes.push_back(std::move(sphere4));
    shapes.push_back(std::move(sphere5));
    shapes.push_back(std::move(light_bulb));
    shapes.push_back(std::move(light_bulb2));
    shapes.push_back(std::move(sun));
    shapes.push_back(std::move(pic1));
    shapes.push_back(std::move(pic2));
    shapes.push_back(std::move(pic3));
    shapes.push_back(std::move(box1));
    shapes.push_back(std::move(box2));
    shapes.push_back(std::move(box3));
    shapes.push_back(std::move(plank2));
    shapes.push_back(std::move(win1));
    shapes.push_back(std::move(win2));
    shapes.push_back(std::move(plank));
    shapes.push_back(std::move(grass));
    shapes.push_back(std::move(floor));
    shapes.push_back(std::move(wall1));
    shapes.push_back(std::move(wall2a));
    shapes.push_back(std::move(wall2aa));
    shapes.push_back(std::move(wall2b));
    shapes.push_back(std::move(wall2bb));
    shapes.push_back(std::move(wall2c));
    shapes.push_back(std::move(wall2cc));
    shapes.push_back(std::move(wall2d));
    shapes.push_back(std::move(wall2dd));
    shapes.push_back(std::move(wall3));
    shapes.push_back(std::move(wall4));
    shapes.push_back(std::move(cieling));
    shapes.push_back(std::move(mirror));
    shapes.push_back(std::move(bunny));
    shapes.push_back(std::move(bunny2));
    return shapes;
}
