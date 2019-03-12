#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <memory>
class Shape;

class Scene {
public:
  std::vector<std::unique_ptr<Shape>> getFrame();
};

#endif
