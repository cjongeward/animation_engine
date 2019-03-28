# 1 Basic Ray tracer

## Description:
The basic idea behind a ray tracer is pretty straightforward. You create a virtual “scene” on the other side of your computer screen. The scene is made up of shapes and light sources. Then, for each pixel on your screen, you shoot a ray into the scene (a ray is just a line with a starting point and a direction).  The ray collides and reflects with the various objects in the scene tracking color and lighting data which all contributed to the final color of the pixel. It can render very accurate and realistic images but it can also be very computationally expensive.  I’m going to make one.

As with any project, I’m going to start small. What is the most basic implementation I can imagine?  Well, let’s draw a sphere in the middle of the screen.  Simple enough, right?  A sphere is mathematically simple to define; it’s just a point and a radius, and a collision between a ray and a sphere is relatively simple to calculate. So here’s what I’m going to do:
* create a simple sphere object with a position and radius, instantiated in the middle of the scene. 
* create a viewport (or screen) with a resolution of 800x600 and place it 4 units away from the sphere. 
* for each pixel on the screen and generate a ray pointing into the scene and detect if the ray collides with the sphere. If it does, color the pixel red, otherwise color the pixel black. 
* output the image to a bitmap file so I can admire my amazing sphere. 
![](napkins/1-basic.jpg)

## Goals:
* Render a single sphere with a flat color
* Output the image to a bitmap file.

## Result:
![](/1-Basic_Ray_Tracer/tracer/image.bmp)

## Definitions:
* world coordinates:  right handed coordinate system where X is right, Y is up, and Z is out of the screen toward the viewer. 
* Screen coordinates: origin at the top left corner, X is right, Y is down. 


## Implementation:
* Create a viewport:  The Screen struct is an axis aligned viewport facing the negative Z direction. The position member variable defines the bottom left corner and the sizex and sizey represent the 2D size. I’ve also defined two global variables for horizontal and vertical screen resolution, RESX and RESY. These are set to 800 and 600 which will be the resolution of the final image. I’ve made these global variables because I intend to put them in a settings file at some point. 
* Create a Sphere:  The sphere struct is composed of a position and a radius.
* Create a 3D vector:  I need a vector to represent position, direction, and color. I’m sure I can find a good implementation somewhere but for now I’ll just code up my own. 
* Create a Ray: The ray is defined by an origin position and a direction vector. 
* Ray/sphere intersect function:  this function detects if the ray intersects with the sphere and returns a boolean. 
![](napkins/rs-intersect.jpg)
* Bitmap generator:  this is some code I copied from the first website that shows up in a google search. It takes a 2D array of 24 bit colors represented as unsigned ints and writes a bitmap file. 
* The main loop:  The heart of the ray tracer. The main loop goes through each pixel in the screen and generates a ray directed out into the scene. As a simple first step, the rays are all parallel to each other and directed in the negative Z direction. This makes it an orthographic projection. I will implement a perspective projection later on which will create a more realistic 3D image.  For each ray, I call the intersects() function on the ray and the sphere. If they intersect, then we color the pixel red, otherwise we color it black. 
```cpp
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
```

## Lessons learned:
* The first time I ran this, the entire image was red. It was a problem with my intersects() function. I fixed it. The second time I ran it, the entire image was black. It was a problem with my intersects() function. Modeling complicated mathematical equations in code is hard to get right, and this one isn’t even that hard. Usually it’s just a typo or a incorrect sign, but bugs in the equation can be hard to find. So be careful, double check your equations and double check that your code matches the equations. I anticipate debugging equations will be a significant part of this project. 
* Other people are not as excited about my red circle as I am.  Oh well, their loss!


