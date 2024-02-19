#include <optional>
#include <vector>
#include <algorithm>
#include "ArrToBmp.h"
#include "vec.h"
#include "Color.h"
#include "Shapes.h"
#include "Reflection.h"

const int RESX = 800;
const int RESY = 600;
const Color RED{ 0.7f, 0.1f, 0.1f };
const Color WHITE{ 1.f, 1.f, 1.f };
const Color BLACK{ 0.f, 0.f, 0.f };
const Color BACKGROUND_COLOR{ 0.1f, 0.3f, 0.7f };
const float AMBIENT_LIGHT_INTENSITY = 0.5f;

class RayTracer {
  Ray primary;

public:
  RayTracer(const Ray& t_primary) : primary{ t_primary } {}

  Color trace(const std::vector<Sphere>& shapes) {
      Color final_color = BLACK;
      bool bAnyColor = false;
      for (auto& shape : shapes) {
        if (auto reflected = intersects(shape, primary)) {
          bAnyColor = true;
          if (shape.bIsLightSource) {
            final_color = shape.color;
          }
          else {
            final_color = final_color + shape.color * AMBIENT_LIGHT_INTENSITY;
            for (auto& secondary_shape : shapes) {
              if (secondary_shape.bIsLightSource) {
                vec lightDir = secondary_shape.pos - reflected->reflection.pos;
                lightDir.normalize();
                float diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir));
                float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, reflected->norm)).dot(primary.dir)), 50.f);
                constexpr float diffuse_mult = 0.5f;
                constexpr float spec_mult = 0.8f;
                final_color = final_color + shape.color * diffuse_mult * diffuse_light_intensity + secondary_shape.color * spec_mult * specular_light_intensity;
              }
            }
          }
        }
      }
      if (!bAnyColor) {
        final_color = BACKGROUND_COLOR;
      }
      return final_color;
  }
};


int main() {

  Screen screen{ vec{-4.f, -3.f, 0.f}, 8.f, 6.f };
  Sphere sphere{ vec{0.f, 0.f, -4.f}, RED, 1.f };
  Sphere light_bulb{ vec{-10.f, 4.f, 4.f}, WHITE, 1.f };
  Sphere light_bulb2{ vec{-2.f, 1.f, 4.f}, WHITE, 1.f };
  light_bulb.bIsLightSource = true;
  light_bulb2.bIsLightSource = true;
  std::vector<Sphere> shapes({ sphere, light_bulb, light_bulb2 });

  unsigned int* img = new unsigned int[RESX * RESY];
  for (int row = 0; row < RESY; ++row) {
    for (int col = 0; col < RESX; ++col) {
      float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
      float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
      Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
      // for debugging
      if (RESY - row - 1 == 300 && col == 350) {
        int blah = 0;
      }
      RayTracer tracer{ ray };
      img[RESX*(RESY - row - 1) + col] = tracer.trace(shapes);
    }
  }

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

  delete[] img;

  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\3-Specular_Lighting\\tracer\\image.bmp");
}
