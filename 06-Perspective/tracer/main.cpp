#include <vector>
#include "ArrToBmp.h"
#include "vec.h"
#include "Color.h"
#include "Shapes.h"
#include "RayTracer.h"
#include "Scene.h"
#include "RayGenerator.h"
#include "Settings.h"


int main() {
  const Screen screen{ vec{-4.f, -3.f, 0.f}, SCREEN_SIZE_X, SCREEN_SIZE_Y };
  const vec focal_point{0.f, 0.f, FOCAL_DIST};
  PerspectiveRayGenerator rayGenerator{ screen, focal_point };
  Scene scene;
  auto shapes = scene.getFrame();
  unsigned int* img = new unsigned int[RESX * RESY];
  for (int row = 0; row < RESY; ++row) {
    for (int col = 0; col < RESX; ++col) {
      Ray ray = rayGenerator.MakeRay(row, col);
      // for debugging
      if (RESY - row - 1 == 200 && col == 150) {
        int blah = 0;
      }
      const RayTracer tracer{ ray };
      img[RESX*(RESY - row - 1) + col] = tracer.trace(shapes);
    }
  }

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

  delete[] img;
  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\06-Perspective\\tracer\\image.bmp");
}
