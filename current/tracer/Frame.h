#ifndef FRAME_H_
#define FRAME_H_

#include <vector>
#include <memory>
#include "Shapes.h"

class Frame {
private:
  std::vector<std::unique_ptr<Shape>> shapes;

public:
  Frame() {
    shapes.push_back(std::make_unique<Sphere>(Sphere{ vec{0.f, 0.f, -4.f}, 1.f, vec{1.0f, 1.0f, 1.0f}, Material{0.1f, 0.5f, 0.8f, 1000.f}, false }));
    shapes.push_back(std::make_unique<Sphere>(Sphere{ vec{-3.f, 0.f, -2.f}, 1.0f, vec{0.1f, 0.8f, 0.1f}, Material{0.7f, 0.5f, 0.f, 50.f}, false }));
    shapes.push_back(std::make_unique<Sphere>(Sphere { vec{2.f, 2.f, -4.f}, 0.5f, vec{0.1f, 0.1f, 0.8f}, Material{0.5f, 0.2f, 0.f, 100.f}, false }));
   // shapes.push_back(std::make_unique<Plane>(Plane { vec{0.f, 0.f, -6.f}, vec{0.f, std::sqrtf(2.f) / 2, std::sqrtf(2.f) / 2}, vec{0.8f, 0.4f, 0.4f}, Material{0.1f, 0.5f, 0.8f, 50.f}, false }));
    shapes.push_back(std::make_unique<AARect>(AARect { vec{-8.f, -4.f, -15.f}, vec{16.f, 8.f, 0.f}, vec{0.8f, 0.7f, 0.2f}, Material{0.7f, 0.1f, 0.f, 100.f}, false }));
    shapes.push_back(std::make_unique<AARect>(AARect { vec{-8.f, -4.f, 1.f}, vec{16.f, 8.f, 0.f}, vec{0.8f, 0.7f, 0.2f}, Material{0.7f, 0.1f, 0.f, 100.f}, false }));
    shapes.push_back(std::make_unique<AARect>(AARect { vec{-8.f, -4.f, -15.f}, vec{0.f, 8.f, 16.f}, vec{0.8f, 0.7f, 0.2f}, Material{0.7f, 0.1f, 0.f, 100.f}, false }));
    shapes.push_back(std::make_unique<AARect>(AARect { vec{8.f, -4.f, -15.f}, vec{0.f, 8.f, 16.f}, vec{0.8f, 0.7f, 0.2f}, Material{0.7f, 0.1f, 0.0f, 100.f}, false }));
    shapes.push_back(std::make_unique<AARect>(AARect { vec{-8.f, -4.f, -15.f}, vec{16.f, 0.f, 16.f}, vec{0.9f, 0.7f, 0.7f}, Material{0.9f, 0.1f, 0.0f, 100.f}, false }));
    shapes.push_back(std::make_unique<AARect>(AARect { vec{-8.f, 4.f, -15.f}, vec{16.f, 0.f, 16.f}, vec{0.9f, 0.9f, 0.9f}, Material{0.9f, 0.1f, 0.0f, 100.f}, false }));
  //  shapes.push_back(std::make_unique<AARect>(AARect { vec{0.f, 0.f, 5.f}, vec{3.f, -3.f, -5.f}, vec{0.7f, 0.1f, 0.1f}, Material{0.7f, 0.1f, 0.f, 100.f}, false }));
    shapes.push_back(std::make_unique<Sphere>(Sphere { vec{0.f, 3.f, -1.f}, 0.1f, vec{1., 1., 1.}, Material{0.1f, 0.1f, 0.f, 10.f}, true }));
    shapes.push_back(std::make_unique<Sphere>(Sphere { vec{4.f, 0.f, -2.f}, 0.1f, vec{1., 1., 1.}, Material{0.1f, 0.1f, 0.f, 10.f}, true }));
//    shapes.push_back(std::make_unique<Sphere>(Sphere { vec{0.f, -1.f, -7.f}, 0.5f, vec{1., 1., 1.}, Material{0.1f, 0.1f, 0.f, 10.f}, true }));
  }

  const std::vector<std::unique_ptr<Shape>>& getShapeVec() const {
    return shapes;
  }


};

#endif
