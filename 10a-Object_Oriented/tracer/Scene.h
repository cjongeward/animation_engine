#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include <memory>
#include "Shapes.h"

class Scene {
public:
  // Creates a vector of shapes to be rendered
  std::vector<DrawableShape> getFrame();
};

#endif
