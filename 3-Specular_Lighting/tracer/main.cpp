#include <optional>
#include <vector>
#include "ArrToBmp.h"
#include "vec.h"
#include "Color.h"
#include "Shapes.h"
#include "Reflection.h"

const int RESX = 800;
const int RESY = 600;
const Color RED{ 0.7f, 0.1f, 0.1f };
const Color WHITE{ 1.f, 1.f, 1.f };
const Color BACKGROUND_COLOR{ 0.1f, 0.3f, 0.7f };
const float AMBIENT_LIGHT_INTENSITY = 0.5f;

class RayTracer {
  Ray primary;

public:
  RayTracer(const Ray& t_primary) : primary{ t_primary } {}

  Color trace(const std::vector<Sphere>& shapes) {
      float diffuse_light_intensity = 0.f;
      Color final_color = BACKGROUND_COLOR;
      for (auto& shape : shapes) {
        if (shape.bIsLightSource) {
          final_color = shape.color;
        }
        else {
          for (auto& target_shape : shapes) {
            if (auto reflected = intersects(target_shape, primary)) {
              if (!target_shape.bIsLightSource) {
                vec lightDir = target_shape.pos - reflected->reflection.pos;
                lightDir.normalize();
                diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir));
                final_color = final_color + target_shape.color * (AMBIENT_LIGHT_INTENSITY + diffuse_light_intensity);
              }
            }
          }
        }
      }
      return final_color;
  }
};


int main() {

  Screen screen{ vec{-4.f, -3.f, 0.f}, 8.f, 6.f };
  Sphere sphere{ vec{0.f, 0.f, -4.f}, RED, 1.f };
  Sphere light_bulb{ vec{-10.f, 6.f, 4.f}, WHITE, 1.f };
  light_bulb.bIsLightSource = true;
  std::vector<Sphere> shapes({ sphere, light_bulb });

	unsigned int* img = new unsigned int[RESX * RESY];
	for (int row = 0; row < RESY; ++row) {
		for (int col = 0; col < RESX; ++col) {
			float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
			float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
      Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
      RayTracer tracer{ ray };
      img[RESX*(RESY - row - 1) + col] = tracer.trace(shapes);
		}
	}

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

	delete[] img;

  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\2-Diffuse_Lighting\\tracer\\image.bmp");
}
