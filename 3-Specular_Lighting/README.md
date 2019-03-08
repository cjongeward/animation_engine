# 3 Specular lighting

## Description:
My sphere looks like a ball now and not just a circle!  It looks kinda chalky, or maybe like rubber. Now I want to make it look shiny. That means I need to create an element of reflection on the surface so that the light source can be directed at the viewer’s eyeball. 

To simulate diffuse light, we used the dot product of the surface norm and the light direction, completely neglecting the reflection angle. Now we need reflection so we will need a reflection function. The simplest way to implement specular light would be to calculate the reflection ray of the light source from the surface. If the reflection ray goes through the pixel, then we add the light to the surface color for that pixel. This would result in pure mirror-like reflection. But what if I don’t want mirror reflection? And also, my light source is a point, so its reflection would only illuminate a single pixel. That’s not going to work. 

So I will fall back to the dot product again, but this time I’ll be using the dot product of the reflected vector and the ray. This way, the intensity of the illumination will be proportional to the cosine (just like the diffuse illumination), it’s just the cosine of different vectors this time. 

So, pure reflection gives me a mirror, but the dot product method will result in a kind of fully diffuse reflection that will not look shiny. I need to be able to tune the shininess. We do that with an exponent, we’ll call it the specular exponent. Both the ray direction vector and the reflection vector are unit vectors so the dot product will always be <= 1 (see lessons learned for horror stories involving non normalized vectors).  Applying an exponent that is greater than 1 to the dot product will help localize the reflected light. A small specular exponent of 10ish will result in a slightly shiny surface resembling old plastic. A high exponent of 250ish will give us a much shinier surface like, I don’t know, shiny plastic or something. This method is referred to as Bling-Phong shading. It’s also worth mentioning that the diffuse implementation from the previous project is called Lambertian shading. 

## Goals:
* Implement specular shading on the sphere
* Support multiple light sources
* Abstract the tracer into its own class 

## Result:
![](/3-Specular_Lighting/tracer/image.bmp)

## Implementation:
* First a bit of cleanup. Let’s find a home for all the free functions that are in main. I moved the sphere/ray intersect function to Shapes.h. I figure this will be a good spot for it to live. I will be implementing more shapes here and will need to implement intersect functions for them all.  I also moved the reflect() function to its own file, Reflection.h.   
* In the previous project, I hardcoded a light source to the left behind the viewport. Now I want a way of adding multiple light sources to a scene dynamically. A light source could be a sphere so I want to be able to add a light source to my std::vector of spheres and have the ray tracer treat it like a light source and even draw the light source if it is in the viewing frustum.  As a temporary implementation, I’m adding a Boolean to the sphere to indicate whether it is a light source. I’m not sure how I’ll clean this up yet. In other implementations I’ve seen, there is a separate container of light sources, but any shape should be able to be a light source and any surface that reflects light is also essentially a light source.  It seems there is a blurry line between light sources and shapes so I want to keep shapes and light sources together. Eventually, maybe I’ll include an intensity property with the shapes to determine if they emit light. For now though, it’s just a Boolean. 
* Implement the specular shading equation. This illuminates the surface proportional to the cosine of the angle between the primary ray and the reflection vector of the light source from the surface. Then the specular exponent is applied. 
```cpp
float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, reflected->norm)).dot(primary.dir)), 50.f);
```
* Now I have three shading components contributing to the color of the surface.  I calculate each of the components separately, then add the together to produce the final color. 
```cpp
const float AMBIENT_LIGHT_INTENSITY = 0.5f;
```
```cpp
float diffuse_light_intensity = std::max(0.f, reflected->norm.dot(lightDir));
```
* A color can only have values between 0 and 1. Since I add colors but never subtract any, it’s easy for the colors to become saturated so I applied a multiplier for the specular and diffuse components of light intensity. This allows me to tune the brightness of the final image. This will eventually become part of the reflection properties of each individual shape, but for now it lives in the main loop. 
```cpp
               constexpr float diffuse_mult = 0.5f;
                constexpr float spec_mult = 0.8f;
                final_color = final_color + shape.color * diffuse_mult * diffuse_light_intensity + secondary_shape.color * spec_mult * specular_light_intensity;
```





