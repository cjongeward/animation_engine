#include <vector>
#include "ArrToBmp.h"
#include "vec.h"
#include "Color.h"
#include "Shapes.h"
#include "RayTracer.h"
#include "Scene.h"
#include "RayGenerator.h"
#include "Settings.h"

// for timing
#include <string>
#include <sstream>
#include <chrono>

void transform(std::vector<std::unique_ptr<Shape>>& shapes) {
  mat cam_pos = mat::translation(-vec{-8.f, 3.f, -1.f});
  mat cam_rot = mat::rotation(PI4, PI4/3.f, 0.f);
  mat xform = cam_rot * cam_pos;
  for(auto& shape : shapes) {
    shape->transform(xform);
  }
}

int main() {
  const Screen screen{ vec{-SCREEN_SIZE_X/2.f, -SCREEN_SIZE_Y/2.f, 0.f}, SCREEN_SIZE_X, SCREEN_SIZE_Y };
  const vec focal_point{0.f, 0.f, FOCAL_DIST};
  PerspectiveRayGenerator rayGenerator{ screen, focal_point };
  Scene scene;
  auto shapes = scene.getFrame();
  transform(shapes);
  unsigned int* img = new unsigned int[RESX * RESY];
  for (int row = 0; row < RESY; ++row) {
    for (int col = 0; col < RESX; ++col) {
      std::vector<Ray> rays = rayGenerator.MakeRay(row, col);
      // for debugging
      if (RESY - row - 1 == 595 && col == 400) {
        int blah = 0;
      }
      // get average color for all rays in the pixel
      Color final_color = BLACK;
      for (auto& ray : rays) {
        const RayTracer tracer{ ray };
        final_color += tracer.trace(shapes);
      }
      final_color *= 1.f / rays.size();
      img[RESX*(RESY - row - 1) + col] = final_color;
    }
  }

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

  delete[] img;
  //system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\08-Shadows_Antialiasing\\tracer\\image.bmp");
}
