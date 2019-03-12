#include "Scene.h"
#include "Shapes.h"

std::vector<std::unique_ptr<Shape>> Scene::getFrame()
{
  Sphere sphere{ vec{0.f, 0.f, -4.f}, MIRRORISH, 1.f };
  Sphere sphere2{ vec{-2.5f, -2.f, -2.f}, DULL, 0.75f };
  Sphere sphere3{ vec{2.5f, -1.f, -1.f}, BRIGHT, 0.5f };
  Sphere sphere4{ vec{-2.0f, -1.5f, -4.f}, BRIGHT, 0.5f };
  Sphere light_bulb{ vec{-10.f, 4.f, 4.f}, LIGHT, 1.f };
  Sphere light_bulb2{ vec{-2.f, 1.f, 4.f}, LIGHT, 1.f };
  Triangle tri{ vec{0.f, -1.f, -2.f}, vec{0.f, -2.f, -2.f}, vec{2.f, -2.f, -2.f}, DULL };
  Triangle tri2{ vec{-3.f, 2.f, -2.f}, vec{0.f, 2.f, -2.f}, vec{-2.f, -1.f, -2.f}, BRIGHT };
  Rect rect{ vec{1.f, 1.8f, -6.f}, vec{1.f, 1.f, -6.5f}, vec{0.5f, 2.f, -6.5f}, BRIGHT };
  Rect rect2{ vec{1.f, 1.8f, -6.f}, vec{1.f, 1.f, -6.5f}, vec{1.5f, 2.f, -6.5f}, BRIGHT };
  Rect rect3{ vec{1.f, 1.8f, -6.f}, vec{0.5f, 2.f, -6.5f}, vec{1.5f, 2.f, -6.5f}, BRIGHT };
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Sphere>(sphere));
  shapes.push_back(std::make_unique<Sphere>(sphere2));
  shapes.push_back(std::make_unique<Sphere>(sphere3));
  shapes.push_back(std::make_unique<Sphere>(sphere4));
  shapes.push_back(std::make_unique<Sphere>(light_bulb));
  shapes.push_back(std::make_unique<Sphere>(light_bulb2));
  shapes.push_back(std::make_unique<Triangle>(tri));
  shapes.push_back(std::make_unique<Triangle>(tri2));
  shapes.push_back(std::make_unique<Rect>(rect));
  shapes.push_back(std::make_unique<Rect>(rect2));
  shapes.push_back(std::make_unique<Rect>(rect3));
  return shapes;
}
