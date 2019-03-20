# 5 Shapes


## Description:
Shiny spheres, dull spheres, mirrory spheres… I have a lot of spheres in my scene, but there’s only so much we can do with spheres. I want to draw boxes, sticks, maybe a floor and some walls. I want to draw triangles so that I can import a triangle mesh of a dinosaur. My daughter wants to see a dinosaur knocking over blocks.  That seems like a good goal.  So I’m going to need more shapes. 

A shape in this raytracer is made up of a few member variables that define the shape and position, and an intersects() function that detects a collision with a ray and calculates the hit point and the reflection. Right now, my tracer iterates a std::vector of spheres. I’ll change this to be a std::vector of polymorphic Shape objects. The Sphere and any other shape I created will all inherit from the Shape class and implement the mandatory intersects() method. 

I will also consider implementing a double dispatch (visitor) pattern for the collision detection. I could easily just call the Shape::intersects(Ray) function but I think a visitor pattern will be useful for the following reasons.
* I feel that MyRay.intersects(myShape) feels more natural than myShape.intersects(myRay)
* I will eventually want to be able to test for collisions between any two arbitrary shapes (later on when I implement physics and bounding boxes and stuff)
* This is a fun project that no one is relying on so I over engineer whatever I want. 

Another class I want to introduce in this project is a Scene builder. Right now I’m creating all my shapes at the top of main(). I will move this to a Scene builder class. Ultimately, when I get to the animation part of this project, the scene class will be responsible for delivering each frame of the animation… although, I haven’t totally thought this out yet so.., we’ll see. 

## Goals:
* Create more shapes. Triangle, Rectangle, Disks, Planes, and Tubes.
* Design a better OO approach to shape collisions
* Change the std::vector of Spheres to a std::vector of Shapes. 
* Create a scene builder

## Result:
![](/05-Shapes/tracer/image.bmp)

## Implementation:
* First, I’ll create a Shape base class with a pure virtual intersects_with(Ray) method.  All shapes that inherit from the class are required to provide an implementation to detect a collision with a Ray. Pretty straightforward so far. 

Now, I want to be able to call Ray.intersects_with(Shape) and I want to implement double dispatch to do it but I’ve dug myself into a few holes that’ll prevent me from doing that for now. First, the Ray class does not inherit from Shape. I’ve been treating the Shape class as a 2D or 3D object with a surface that can be rendered so the Shape class has a SurfaceProperties instance. A Ray is not a shape since it is a single dimensional conceptual object so it can’t participate in a visitor pattern that handles Shape collisions. 

Second, I’ve designed the intersects() method to return a std::optional containing a reflection data packet that includes the reflected Ray. If I add an intersects method to the Ray class, it will have a dependency on the ReflectionData class. But the ReflectionData class has a dependency on the Ray class. So that sucks. I’ll need to rethink this all at some point. For now, I’ll just bite the bullet and call myShape.intersects(myRay). 
```cpp
```

* Now to make some more shapes. I’ll start by creating a Triangle class. I define a triangle with three points. My reflection function will flip the norm if it’s facing the wrong direction so the order of the points doesn’t matter. 

As for the ray/triangle intersects() function, I’ll skip over most of the details, but the basic steps are:
calculate the point where the ray intersects the plane defined by the triangle (call it P) 
Convert the point to barycentric coordinates (using beta and gamma as the basis vectors)
If P.gamma > 0, P.beta>0, and P.beta+P.gamma < 1, then we have a collision. 

* Create a Rectangle class. I made the rectangle class almost the exact same as the triangle class. Like the Triangle class, the Rectangle class is also defined by three points. The origin point and the two adjacent points. It extrapolates the fourth point in the intersects() function, so really my Rectangle is actually a parallelogram. I should probably rename it such. 

The intersects() function is implemented the exact same way as the triangle. The only difference is the collision test between P and the barycentric coordinates. The collision occurs if 0 < P.gamma < 1 and 0 < P.beta < 1. 

Since 97% of the intersects() function is identical, I created a free function called barycentric_intersects() that accepts a std::function for the collision test. 

* Lastly, I created a Scene Class. Now I can move the creation of the std::vector of shapes into its own class. The factory method is called getFrame(). The motivation behind this name is that it will eventually be used to build each sequential frame in an animation, but that won’t be for a while. Until then, I’m just using it as a place to assemble my scene. 

## Lessons Learned:
* t must be > 0
* collisions are ugly
* my improvised collision is somehow making my triangles translucent.  How the fuck is the mirror showing up in the purple triangle?!  While I was working on the next project, I noticed the norm for the triangles and spheres was pointing in the wrong direction. This was causing the shapes to be illuminated incorrectly. Notice the cube in the image is darker on the left even though the light source is on the left. Oops…
* no shadows
* gonna need a matrix soon

