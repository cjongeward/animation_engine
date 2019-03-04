# 2 Diffuse lighting

## Goals:
* apply ambient lighting to the entire sphere. 
* light the sphere from the side and apply a diffuse shading equation.

## Result:
![](/2-Diffuse_Lighting/tracer/image.bmp)

## Description:
The last exercise gave me a bright red circle. I know that it’s really a red sphere floating 4 units away from the camera, but to everyone else it’s a red circle. I need to add some lighting to the scene and shade the sphere so that it actually looks like a sphere.

I will apply three different types of lighting over the next two projects, ambient lighting, diffuse lighting, and specular lighting. 
* ambient lighting is used to illuminate a surface that is not exposed to any direct lighting. In the real world, light repeatedly bounces off surfaces and molecules in the atmosphere to indirectly illuminate surfaces. I will approximate that lighting by simply illuminating every surface in the scene with a low level of light. There are techniques to make ambient lighting more realistic and I’ll expand on this in a later exercise. 
* Diffuse lighting and specular lighting describe how light reflects from a surface at opposite ends of a spectrum.  So any light reflecting from a surface lies somewhere between fully diffuse and fully specular. Fully diffuse reflection means the light is reflected evenly in every direction in the hemisphere of the incident light. This creates a color that appears flat. Fully specular reflection means that the light will reflect in one direction. This would create the appearance of a mirror. I’ll implement fully diffuse reflection in this exercise and then add a specular component in the next exercise. 

## Implementation:
* move my vector class into its own file. I should probably consider using an existing vector implementation, but for now I’ll keep using my own until it gets too annoying and tedious. Add all the required operators plus the basic vector operations like cross product, normalize, etc. 
* make a Color class that is backed by a vec3. Add a method to clamp the values between 0 and 1. For now I will just limit the color values with min and max. This creates a weird looking shading when the color becomes saturated (greater than one).  There are other methods for clamping that make the image look more realistic. I will apply them in a future exercise. 
* Move the sphere into a container so I can iterate through multiple spheres. The sphere will become a polymorphic shape object eventually. 
* Apply ambient and diffuse shading to the sphere. Hard code a light source. 

