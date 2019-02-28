#include "ArrToBmp.h"

const int RESX = 800;
const int RESY = 600;

struct vec {
  float x, y, z;
  vec(float t_x, float t_y, float t_z) : x{ t_x }, y{ t_y }, z{ t_z } {}
  vec operator-(const vec& rhs) const {
    return vec{ x - rhs.x, y - rhs.y, z - rhs.z };
  }
  vec operator*(float rhs) const {
    return vec{ x*rhs, y*rhs, z*rhs };
  }
  float dot(const vec& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  float mag2() const {
    return x * x + y * y + z * z;
  }
};

struct Ray {
  vec pos;
  vec dir;
  Ray(const vec& t_pos, const vec& t_dir) : pos{ t_pos }, dir{ t_dir } {}
};

struct Sphere {
  vec pos;
  float radius;
  unsigned color;
  Sphere(const vec& t_pos, unsigned t_color, float t_radius) : pos{ t_pos }, color{ t_color }, radius{ t_radius } {}
};

struct Screen {
  vec pos;
  float sizex;
  float sizey;
  Screen(const vec& t_pos, float t_sizex, float t_sizey) : pos{ t_pos }, sizex{ t_sizex }, sizey{ t_sizey }{}
};

bool intersects(const Sphere& sphere, const Ray& ray) {
  vec ray2sph = sphere.pos - ray.pos;
  vec ray2sph_proj_ray = ray.dir * ray2sph.dot(ray.dir);
  float min_dist2 = ray2sph.mag2() - ray2sph_proj_ray.mag2();
  if (min_dist2 <= sphere.radius*sphere.radius) {
    return true;
  }
  return false;
}

unsigned RED = 0xFF000000;
unsigned BLACK = 0x00000000;

int main() {
  Screen screen{ vec{-4.f, -3.f, 0.f}, 8.f, 6.f };
  Sphere sphere{ vec{0.f, 0.f, -4.f}, RED, 1.f };

	unsigned int* img = new unsigned int[RESX * RESY];
	for (int row = 0; row < RESY; ++row) {
		for (int col = 0; col < RESX; ++col) {
			float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
			float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
      Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
      unsigned color = BLACK;
      if (intersects(sphere, ray)) {
        color = sphere.color;
      }
      img[RESX*(RESY - row - 1) + col] = color;
		}
	}

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

	delete[] img;

  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\1-Basic_Ray_Tracer\\tracer\\image.bmp");
}
