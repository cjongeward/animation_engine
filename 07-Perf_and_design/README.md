# 6 Perspective


## Description:
Perspective and cleanup

## Goals:
* Create a RayGenerator 
* Implement perspective projection

## Result:
![](/06-Perspective/tracer/image.bmp)

## Implementation:
* RayGenerator class with Orthographic and Perspective implementation
* fixed norm, display front only problem
* Made a room with a mirror
* moved more settings into settings.h so its easier to play
* made color and global colors constexpr

## Lessons Learned:
* For triangles and rectangles, the order of points matters.  I made the reflect() function automatically flip the norm if it is facing the wrong way so I wouldn’t have to worry about which side is the front, but the norm appears in a lot of places.  I can’t think of a clean way to make it work so I’ll just make these shapes have a front.  Besides, I’ll be doing textures and bump maps soon.  I’ll need a front for those.
* all triangles should be defined counter clockwise so norm will point out the front, rects defined with pos1 at the center.  I got my norm backwards so shading didn’t work right, but I also flipped my sign for the t check so the correct side still rendered.
* in the mirror, I’m seeing specular reflections on the wrong side of the sphere.
* specular and diffuse shading dont transmit through the mirror

