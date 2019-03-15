# 5 Shapes


## Description:
* Create a bunch of shapes

## Goals:
* Create more shapes. Triangle, rect, disk, plane, tube
* Design a better OO approach to shape collisions
* Sphere vector becomes a shape vector
* Create scene builder
* maybe create a surface builder
* perspective ray generator

## Result:
![](/05-Shapes/tracer/image.bmp)

## Implementation:
* Create a Shape base class and change the std::vector of spheres to a std::vector of shapes
* Implement double dispatch for Ray - Shape intersect function
* Create triangle class and intersects function
* Create rectangle class.  Intersects function is same as triangle with a slightly different comparison function.  Use lambda.
* Scene class 

## Lessons Learned:
* t must be > 0
* collisions are ugly
* my improvised collision is somehow making my triangles translucent.  How the fuck is the mirror showing up in the purple triangle?!
* no shadows
* gonna need a matrix soon
