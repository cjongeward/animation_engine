#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <memory>
struct Shape;

class Scene {
public:
  // Creates a vector of shapes to be rendered
  std::vector<std::unique_ptr<Shape>> getFrame();
};

#endif
