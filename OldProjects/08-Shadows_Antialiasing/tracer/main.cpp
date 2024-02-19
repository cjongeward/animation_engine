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
#include <Windows.h>


int main() {
  const Screen screen{ vec{-4.f, -3.f, 0.f}, SCREEN_SIZE_X, SCREEN_SIZE_Y };
  const vec focal_point{0.f, 0.f, FOCAL_DIST};
  PerspectiveRayGenerator rayGenerator{ screen, focal_point };
  Scene scene;
  auto shapes = scene.getFrame();
  unsigned int* img = new unsigned int[RESX * RESY];
  auto start_time = std::chrono::high_resolution_clock::now();
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
  auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
  auto ns = elapsed_time.count();
  std::stringstream stream;
  stream << "elapsed time: " << ns/1000000 << " ms \n";
  OutputDebugString(stream.str().c_str());

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

  delete[] img;
  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\08-Shadows_Antialiasing\\tracer\\image.bmp");
}
