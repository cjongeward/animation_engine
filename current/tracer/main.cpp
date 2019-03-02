#include <optional>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "ArrToBmp.h"
#include "vec.hpp"
#include "Shapes.h"
#include "Settings.h"
#include "RayGenerator.h"
#include "Frame.h"

const vec bgColor{ 0.0f, 0.5f, 0.7f };


class RayTrace {
public:
	Ray initialRay;
	Ray currentRay;
	const int MaxReflects = 5;
  int curReflects = 0;
	const int NumRays = 100;
  Shape* nearestShape = nullptr;

	RayTrace(const Ray& _start) : initialRay{ _start }, currentRay{ _start } { }

	vec trace(const std::vector<std::unique_ptr<Shape>>& shapes) {
		std::optional<Ray> nextRay = std::nullopt;
    vec norm{ 1.f, 0.f, 0.f };
    auto shapeToSkip = nearestShape;
		for (auto& shape : shapes) {
      if (shape.get() != shapeToSkip) {
        auto reflectData = shape->intersectsWith(currentRay);
        if (reflectData) {
          if (!nextRay) {
            nextRay = reflectData->reflectionRay;
            norm = reflectData->norm;
            nearestShape = shape.get();
          }
          else {
            auto dist2 = (currentRay.pos - nextRay->pos).mag2();
            auto newdist2 = (currentRay.pos - reflectData->reflectionRay.pos).mag2();
            if (newdist2 < dist2) {
              nextRay = reflectData->reflectionRay;
              norm = reflectData->norm;
              nearestShape = shape.get();
            }
          }
        }
      }
		}

    if (!nextRay || curReflects++ == MaxReflects) {
      return bgColor;
    }
    else {
      currentRay = *nextRay;
      auto curShape = nearestShape;
      if (!curShape->bLightSource) {
        vec reflectedColor = trace(shapes);
        float difuse_light = 0;
        float spec_light = 0;
        for (auto& shape : shapes) {
          if (shape->bLightSource) {
            auto lightPos = shape->pos;
            auto lightColor = shape->color;
            auto lightDir = lightPos - curShape->pos;
            lightDir.normalize();
            difuse_light += std::max(0.f, norm.dot(lightDir)); // doesnt work right for flat surfaces
            spec_light += std::powf(std::max(0.f, (reflection(lightDir*-1.f, norm) * -1.f).dot(initialRay.dir)), curShape->material.spec_coef);
          }
        }
        vec curColor =
          (curShape->color * difuse_light * curShape->material.difuse_mult) +
          (vec{ 1.f, 1.f, 1.f } *spec_light *curShape->material.spec_mult) +
          reflectedColor * curShape->material.reflect_mult;
        return curColor;
      }
      else {
        return nearestShape->color;
      }
    }
    return bgColor;
	}
};


int main() {
	Screen screen;
  Frame frame;
  std::unique_ptr<RayGenerator> rayGen = std::make_unique<PerspectiveRayGenerator>(vec{ 0.f, 0.f, 1.f }, screen.pos + vec{ screen.sizex / 2.f, screen.sizey / 2.f, 0.f }, 10.f);
	unsigned int* img = new unsigned int[screen.resx * screen.resy];
	for (int row = 0; row < screen.resy; ++row) {
		for (int col = 0; col < screen.resx; ++col) {
			float px = screen.pos.x + screen.sizex * static_cast<float>(col) / screen.resx;
			float py = screen.pos.y + screen.sizey * static_cast<float>(row) / screen.resy;
      if (row == 100 && col == 100) {
        int blah = 0;
      }
      Ray r = rayGen->generateRay(vec{ px, py, 0.f });
			RayTrace trace(r);
			auto color = trace.trace(frame.getShapeVec());
      color.clamp();
			img[screen.resx*(screen.resy - row - 1) + col] = toColor(color);

		}
	}

	bool result = intarray2bmp::intarray2bmp("foo.bmp", img, SCREEN_RES_Y, SCREEN_RES_X);

	delete[] img;

  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\current\\tracer\\foo.bmp");
}
