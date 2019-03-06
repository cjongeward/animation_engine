#include <vector>
#include <algorithm>
#include "ArrToBmp.h"
#include "vec.h"
#include "Color.h"
#include "Shapes.h"
#include "RayTracer.h"
#include "Settings.h"


int main() {

  Screen screen{ vec{-4.f, -3.f, 0.f}, 8.f, 6.f };
  Sphere sphere{ vec{0.f, 0.f, -4.f}, MIRRORISH, 1.f };
  Sphere sphere2{ vec{-2.5f, -2.f, -2.f}, DULL, 0.75f };
  Sphere sphere3{ vec{2.5f, -1.f, -1.f}, BRIGHT, 0.5f };
  Sphere light_bulb{ vec{-10.f, 4.f, 4.f}, LIGHT, 1.f };
  Sphere light_bulb2{ vec{-2.f, 1.f, 4.f}, LIGHT, 1.f };
  light_bulb.bIsLightSource = true;
  light_bulb2.bIsLightSource = true;
  std::vector<Sphere> shapes({ sphere, sphere2, sphere3, light_bulb, light_bulb2 });

  unsigned int* img = new unsigned int[RESX * RESY];
  for (int row = 0; row < RESY; ++row) {
    for (int col = 0; col < RESX; ++col) {
      float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
      float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
      Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
      // for debugging
      if (RESY - row - 1 == 330 && col == 360) {
        int blah = 0;
      }
      RayTracer tracer{ ray };
      img[RESX*(RESY - row - 1) + col] = tracer.trace(shapes);
    }
  }

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

  delete[] img;

  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\04-Reflection\\tracer\\image.bmp");
}
