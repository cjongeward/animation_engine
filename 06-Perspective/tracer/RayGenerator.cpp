#include "RayGenerator.h"
#include "Settings.h"

Ray OrthographicRayGenerator::MakeRay(int row, int col) const
{
  float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
  float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
  Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
  return ray;
}

Ray PerspectiveRayGenerator::MakeRay(int row, int col) const
{
  float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
  float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
  vec pos = vec{ px, py, 0.f };
  vec dir = pos - focal_point;
  dir.normalize();
  Ray ray{ pos, dir };
  return ray;
}

