#include <optional>
#include "ArrToBmp.h"
#include "vec.h"
#include "Color.h"
#include "Shapes.h"

const int RESX = 800;
const int RESY = 600;

struct ReflectionData {
  Ray reflection;
  vec norm;
  ReflectionData(const Ray& t_reflection, const vec& t_norm) : reflection{ t_reflection }, norm{ t_norm }{}
};

vec reflect(const vec& orig, const vec& norm) {
  auto orig_dot_norm = orig.dot(norm);
  auto real_norm = norm;
  // negate the norm if it is pointing in the wrong direction
  if (orig_dot_norm > 0) {
    real_norm = real_norm * -1.f;
  }
  return orig - real_norm * 2.f * orig.dot(real_norm);
}

std::optional<ReflectionData> intersects(Sphere s, Ray incident) {
  auto v_ray2sph_center = s.pos - incident.pos;
  auto v_r2s_proj_ray = v_ray2sph_center.dot(incident.dir); // projection of ray_origin_to_sphere onto ray
  if (v_r2s_proj_ray < 0.f) {  // if sphere is behind ray origin
    return std::nullopt;
  }
  auto v_ray2sph_bis = incident.dir * v_r2s_proj_ray; // vector from ray origin to midway through the sphere along the ray
  auto v_min_dist = v_ray2sph_bis - v_ray2sph_center; // vector from sphere center to closest point on the ray 
  float d2 = v_min_dist.mag2();
  float r2 = s.radius*s.radius; 
  if (d2 > r2) { // if min distance between ray and sphere is greater than radius, then no intersection
    return std::nullopt;
  }
  float cd2 = r2 - d2; // ratio of v_ray2sph_bis that is inside the sphere... squared
  float ratio = 1.f - std::sqrtf(cd2) / v_ray2sph_bis.mag(); // the remaining portion of v_ray2sph_bis leads to the surface of the sphere
  auto v_ray2sph_surface = v_ray2sph_bis * ratio;
  auto p_sphere_surface = incident.pos + v_ray2sph_surface; 
  auto v_norm = p_sphere_surface - s.pos;
  v_norm.normalize();
  auto v_reflection = reflect(incident.dir, v_norm);
  return std::make_optional(ReflectionData(Ray(p_sphere_surface, v_reflection), v_norm));
}

int main() {
  const Color RED{ 0.7f, 0.1f, 0.1f };
  const Color BACKGROUND_COLOR{ 0.1f, 0.3f, 0.7f };
  const float AMBIENT_LIGHT_INTENSITY = 0.5f;
  const vec LIGHT_POS{ -10.f, 4.f, 6.f };

  Screen screen{ vec{-4.f, -3.f, 0.f}, 8.f, 6.f };
  Sphere sphere{ vec{0.f, 0.f, -4.f}, RED, 1.f };

	unsigned int* img = new unsigned int[RESX * RESY];
	for (int row = 0; row < RESY; ++row) {
		for (int col = 0; col < RESX; ++col) {
			float px = screen.pos.x + screen.sizex * static_cast<float>(col) / RESX;
			float py = screen.pos.y + screen.sizey * static_cast<float>(row) / RESY;
      Ray ray{ vec{px, py, 0.f}, vec{0.f, 0.f, -1.f} };
      float diffuse_light_intensity = 0.f;
      Color final_color = BACKGROUND_COLOR;
      if (auto reflected = intersects(sphere, ray)) {
        vec lightDir = LIGHT_POS - reflected->reflection.pos;
        lightDir.normalize();
        diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir));
        final_color = sphere.color * (AMBIENT_LIGHT_INTENSITY + diffuse_light_intensity);
      }
      img[RESX*(RESY - row - 1) + col] = final_color;
		}
	}

  bool result = intarray2bmp::intarray2bmp("image.bmp", img, RESY, RESX);

	delete[] img;

  system("start  C:\\WINDOWS\\system32\\mspaint.exe C:\\Users\\caj34\\Documents\\repos\\animation_engine\\2-Diffuse_Lighting\\tracer\\image.bmp");
}
