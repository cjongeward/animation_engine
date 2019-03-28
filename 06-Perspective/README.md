# 6 Perspective


## Description:
So I have a bunch of shapes floating in front of a blue background. I would like to turn this into a closed scene by adding a floor, ceiling, and some walls. The problem is that orthographic projection is going to make it look wrong. Since all the rays are parallel in orthographic projection, any surface that is parallel to the rays will not be rendered. If I wrap my shapes in a room, you’re not going to see most of the walls. 

But orthographic projection is not realistic anyways. What we need is for the rays to originate at a point in front of the screen (we’ll call it the focal point or eyeball location) and pass through each of the pixels on the screen. This makes the rays fan out so that far objects appear smaller, just like in real life.  This is called perspective projection. So in this project, I’m going to change the way we create rays. 

Right now, I’m generating my rays in the main method. For each pixel, I calculate the location of that pixel in world coordinates, then create a ray originating at that point and directed in the negative Z direction. I want to encapsulate that into a RayGenerator class and make the implementation swappable between orthographic and perspective.  So I’ll create a pure virtual class called RayGenerator with an implementation for each type of projection. It will have a method that accepts a pixel location and returns the Ray for that pixel. 

I like this idea (for now) and I can see an opportunity to use this mechanism in the future when I may need to generate multiple rays per pixel for anti aliasing. I can adjust this method to return a container of rays instead of just one. 

## Goals:
* Create a RayGenerator class
* Implement perspective projection

## Result:
![](/06-Perspective/tracer/image.bmp)

## Implementation:
* First I’ll build the RayGenerator classes, then I’ll build a scene that shows off perspective projection. 

The RayGenerator class has a single pure virtual method, makeRay() that takes a row and column as its parameters and generates a Ray originating at the pixel. The derived classes are constructed with all the data they need to calculate the position and direction of each Ray. The main function loops through each pixel and calls the Ray generator to produce the ray that is passed to the tracer. 

I have two implementations of the RayGenerator class,  OrthographicRayGenerator and PerspectiveRayGenerator. Each of them is constructed with a Screen object which they use to calculate the position and orientation of each pixel. The perspective generator has an additional parameter, the focal point. The direction of each Ray is along the line between the focal point and the pixel. We can vary the field of view by moving the focal point closer or farther from the screen. 
```cpp
int main() {
  const Screen screen{ vec{-4.f, -3.f, 0.f}, SCREEN_SIZE_X, SCREEN_SIZE_Y };
  const vec focal_point{0.f, 0.f, FOCAL_DIST};
  PerspectiveRayGenerator rayGenerator{ screen, focal_point };
……..
  for (int row = 0; row < RESY; ++row) {
    for (int col = 0; col < RESX; ++col) {
      Ray ray = rayGenerator.MakeRay(row, col);
      const RayTracer tracer{ ray };
      …….
    }
  }
  ……….
}
```
```cpp
class RayGenerator {
public:
  virtual Ray MakeRay(int row, int col) const = 0;
};

class OrthographicRayGenerator : public RayGenerator {
private:
  Screen screen;
public:
  OrthographicRayGenerator(const Screen& t_screen) : screen{ t_screen } {}
  Ray MakeRay(int row, int col) const override;
};

class PerspectiveRayGenerator : public RayGenerator {
private:
  Screen screen;
  vec focal_point;
public:
  PerspectiveRayGenerator(const Screen& t_screen, const vec& t_focal_point) : focal_point{ t_focal_point }, screen{ t_screen }{}
  Ray MakeRay(int row, int col) const override;
};
```
```cpp
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
```

* Now that I have perspective projection working, let’s show it off. I expanded the scene to include walls, a floor, and a ceiling. I moved one of the light sources into the frame so you can see it’s diffuse effect on the ceiling. I also put a mirror on the wall because, why not?  It looks cool. But I notice a few problems...

* The purple triangle still has a weird circle on it from the previous project. The cube appears to be lit incorrectly, also visible in the previous project. In fact, if I put a light source right in front of a surface, it’s not lighting up the way I would expect. So what’s the problem?

It turns out, the norm of some of the surfaces is pointing in the wrong direction.  I didn’t think this would be a big deal because I was flipping the norm in my Reflect() function if it was pointing in the wrong direction, but I didn’t realize the norm was also being used toward the end of the trace() function and it also needs to be flipped there.  Instead of flipping it there too, I started thinking about applying textures.  I think it will be difficult to deal with textures if I render both sides of a surface so I am now only rendering the side with the positive norm.

So, from now on, surfaces defined in a counter clockwise order are facing the camera and will be drawn.  Others will be skipped.  This will also improve performance because I can skip intersection tests if the normal is facing away from the ray (which is nice because performance is starting to become an issue).

* I moved more global settings to Settings.h.  This will make it easier to play with things lie focal distance and ambient light intensity.

* Finally, I intend to make a SurfaceProperties factory at some point but, until then, I’m just defining some constant surface properties.  I might as well make them constexpr.  But to do this, I needed to make just about everything in the vec and SurfaceProperties classes constexpr.  Well, I guess this gets my one step closer to a fully constexpr ray tracer...

## Lessons Learned:
* Barycentric coordinates may not be the best way to detect collisions for a Rect (actually a parallelogram).  I have to define the three points in a specific order to get the surface facing the correct direction, and I have to make sure I define the correct points, otherwise the shape will be wrong.  Maybe I’ll look into other methods later.

* Mirrors help remind me that diffuse and specular shading don’t care about reflections yet.  So a light source shining through a mirror will no illuminate a surface.  I’ll need to figure out how to deal with that too.

