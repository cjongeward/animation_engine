# 2 Diffuse lighting



## Description:
The last exercise gave me a bright red circle. I know that it’s really a red sphere floating in virtual space 4 units away from the camera, but everyone else just thinks it’s a red circle. I need to add some lighting to the scene and shading to the sphere so that it actually looks like a sphere.

I will apply three different types of shading to the sphere over the next two projects, ambient, diffuse, and specular. 
* ambient lighting is used to illuminate a surface that is not exposed to any direct light. In the real world, a beam of light repeatedly bounces off surfaces and particles in the atmosphere and whatnot to indirectly illuminate other surfaces. Ambient lighting approximates this by simply illuminating every surface in the scene with a constant low level of light. There are techniques to make ambient lighting more realistic and I’ll expand on these later. 
* Diffuse shading and specular shading both describe how light reflects from a surface, but they represent opposite ends of the shininess spectrum.  Any light reflecting from a surface lies somewhere between fully diffuse and fully specular. Fully diffuse reflection means the light is reflected evenly in every direction in the hemisphere of the surface norm. This creates a color that appears flat and chalky. Fully specular reflection means that the light source will reflect off the surface in one direction. This would create the appearance of a mirror. I’ll implement fully diffuse reflection in this project and then add a specular component in the next project. 
![](napkins/diffuse.jpg)

## Goals:
* Apply ambient lighting to the entire sphere. 
* Light the sphere from the side and apply a diffuse shading equation.

## Result:
![](/2-Diffuse_Lighting/tracer/image.bmp)

## Implementation:
* Move the 3D vector class into its own file: I should probably consider using an existing vector implementation like GLM, but for now I’ll keep using my own until it gets too annoying and tedious. I added all the required operators and the basic vector operations like cross product, normalize, etc. 
* Make a Color class: In the previous project, I represented color with an unsigned int which is required by the bitmap generator.  Now I will make a Color class that uses the 3D vector to store RGB data. It supports addition and multiplication operators so I can combine and scale colors. 

Each individual value in the color should stay between 0 and 1 so I added a method to clamp the values if they go outside that range. For now, it’s pretty simple. I just limit the color values with min and max. This creates a weird effect when the color becomes saturated. There are other methods for clamping that make the image look more realistic. I will apply them in a future project. 

I also wrote an implicit conversion operator to convert the color to an unsigned int. This comes in handy when we assign the color to the image buffer since it expects an unsigned int. 
```cpp
class Color {
  vec color_vec;

public:
  Color(float red, float green, float blue) : color_vec{ red, green, blue } {}
  void clamp() {
    color_vec.x = std::min(1.f, std::max(0.f, color_vec.x));
    color_vec.y = std::min(1.f, std::max(0.f, color_vec.y));
    color_vec.z = std::min(1.f, std::max(0.f, color_vec.z));
  }
  operator unsigned() const {
    Color temp_color = *this;
    temp_color.clamp();
    return (static_cast<unsigned>(255. * temp_color.color_vec.z) << 8) + 
      (static_cast<unsigned>(255. * temp_color.color_vec.y) << 16) + 
      (static_cast<unsigned>(255. * temp_color.color_vec.x) << 24);
  }
}
```
* Move the sphere into a container: I will eventually want to render more than one sphere, and probably other shapes too, so I need a container to put them in. For now, I will put the sphere into a std::vector and change the tracer code to iterate through all the spheres in the std::vector. 
* Apply ambient lighting: I start with a float to set the desired ambient light intensity.  I made it a global float that will live with the other settings. The entire surface of the sphere is painted a dim shade of red the intensity of which is driven by the ambient light intensity variable.  
* Apply diffuse lighting:  First I need to create a light source. For now, I will hardcode a light source at a point to the left and behind the camera.  The intensity of the diffuse illumination on the surface of the sphere is proportional to the cosine of the surface norm and a vector pointing to the light source, so I’ll calculate it using the dot product. This means the side of the sphere that is facing the light will receive maximum illumination and the edges of the sphere roughly 90 degrees and beyond will only receive ambient light. 

Now I need my intersects() function to return more info than just a Boolean. At very least, I need to know if the ray collides with the sphere, where it hits the sphere (the hit point), and the norm at the surface so I can calculate the diffuse light intensity. In the next project when I do specular shading, I’ll also need to know the reflected ray. So I am returning a std::optional from the intersects() function.  If there is no collision, the std::optional is empty. If there is a collision, the std::optional will contain a ReflectionData packet that contains the norm and the reflected ray. Everything I need to trace some rays.
```cpp
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
```
```cpp
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
```

