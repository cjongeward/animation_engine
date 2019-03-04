# 1 Basic Ray tracer

## Goals:
* Render a single sphere with a flat color
* Output the image to a bitmap

## Result:
![](/1-Basic_Ray_Tracer/tracer/image.bmp)

## Description:
As a first step, I want to create a simple sphere model with a position, radius, and color and place it in front of the camera. I create a screen that is 800 x 600 pixels and generate a ray originating from each pixel directed out toward the sphere along the Z axis. If the ray intersects the sphere, I will set the originating pixel’s color to the color of the sphere, otherwise I will set it to black. Finally, I will output the final array of colors to a bitmap and open it in MSPaint to admire my crappy sphere. 

## Definitions:
coordinates system:  right handed coordinate system where X is right, Y is up, and Z is out of the screen toward the viewer. 

## Implementation:
* Create a viewport:  The Screen struct is an axis aligned viewport facing the negative Z direction. The position refers to the bottom left corner and the sizex and sizey represent the 2D size. I’ve also defined two global variables for horizontal and vertical screen resolution. These are set to 800 and 600 which will be the resolution of the final image. I’ll move these globals into a settings file at some point in the future. 
* Create a Sphere:  The sphere is composed of a position and a radius. Simple enough. 
* Create a 3D vector:  I need a vector to represent position, direction, and color. I’m sure I can find a good implementation somewhere but for now I’ll just code up my own. 
* Ray: The ray is defined by an origin vector and a direction vector. 
* Ray sphere intersect function:  this function detects if the ray intersects with the sphere and returns a boolean. 
* Bitmap generator:  this is some code I copied from a website. It takes a 2D array of 24 bit colors and writes a bitmap file. 
* The main loop:  The heart of the ray tracer. The main loop goes through each pixel of the final image and generates a ray directed out into the scene. As a simple first step, the rays will be all be parallel and directed in the negative Z direction. This makes it an orthographic projection. I will implement a perspective projection later on which will create a more realistic 3D image.  For each ray, I will call the intersects() function on the ray and the sphere. If they intersect, then we color the pixel red, otherwise we color it black. 

## Lessons learned:
* The first time I ran this, the entire image was red. It was a problem with my intersects() function. I fixed it. The second time I ran it, the entire image was black. It was a problem with my intersects() function. Modeling complicated mathematical equations in code is hard to get right. Usually it’s just a typo or a incorrect sign, but bugs in the equation can be really hard to find. So be careful, double check your equations and double check that your code matches the equations. I anticipate debugging equations will be a significant part of this project. 
* It’s just a red circle, buts it’s extremely satisfying. I made that circle!


