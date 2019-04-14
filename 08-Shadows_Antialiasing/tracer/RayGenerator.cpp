#include "RayGenerator.h"
#include "Settings.h"

std::vector<Ray> OrthographicRayGenerator::MakeRay(int row, int col) const
{
  float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
  float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
  Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
  return { ray };
}

std::vector<Ray> PerspectiveRayGenerator::MakeRay(int row, int col) const
{
  std::vector<Ray> rays;
  float colf = static_cast<float>(col);
  float rowf = static_cast<float>(row);
  constexpr float increment = 1.f / NUM_LINEAR_SAMPLES_PER_PIXEL;
  for (float col_fine = 0.f; col_fine < 1.f; col_fine += increment) {
    for (float row_fine = 0.f; row_fine < 1.f; row_fine += increment) {
      float px = screen.pos.x + screen.sizex * (colf + col_fine) / RESX;
      float py = screen.pos.y + screen.sizey * (rowf + row_fine) / RESY;
      vec pos = vec{ px, py, 0.f };
      vec dir = pos - focal_point;
      dir.normalize();
      Ray ray{ pos, dir };
      rays.push_back(ray);
    }
  }
  return rays;
}

