# 4 Reflection


## Description:
Ok, so this one took me a minute to wrap my mind around. Up until now, I haven’t really been ray tracing. Yes, I generate a ray and shoot it into the scene, but that’s where it ends.  Once the ray finds a hit point, the “tracing” ends and we switch to object-based shading. We loop through each object in the scene, determine if it’s a light source, then run it through the diffuse and specular equations; no more tracing involved. 

But these equations are really just approximations of what actually should happen. Before I learned about these equations, I had this idea that I could implement diffuse and specular shading and everything in between all at once. Before I go into that though, let me define a full raytracer. 

The full ray tracer starts with the primary ray originating at the pixel and going out into the scene. If it collides with a surface, it reflects off the surface generating a secondary ray. If the secondary ray collides with a surface, it reflects and generates another secondary ray, and so forth and so on. This continues until there is no collision or until we’ve reached the maximum number of secondary rays. Then, the color data from each of the surfaces is combined to calculate the final color of the pixel. This generates a very nice mirror reflection just like the specular equation without the specular exponent.  

So how can we use raytracing to generate something other than a perfect mirror reflection?  We can’t apply a specular exponent in this case. My idea was to shoot multiple rays for each pixel, randomly distort the norm of the surface for each ray, then average all the rays together to color the pixel. More distortion would result in a more diffuse surface. Maybe I’ll try this approach later, but I suspect I would need hundreds of rays per pixel to make this work and that sounds SLOOOOW. 

So, back to mirror reflection. In this project, I will implement mirror-like reflection using actual ray tracing and I will combine it with the existing ambient, diffuse, and specular components. So now I will have four components to add into the final color. 

Since this is not the object-based rendering approach I’ve used previously, I will calculate this component outside of the loop that iterates the shapes. Basically we create a stack of rays, pushing a new one onto the stack each time the previous one collides with a surface, then we unwind the stack and pass the color data from each collision back to the originating ray.  Kinda sounds like recursion to me.  Let’s see what happens...

## Goals:
* Create a sphere that reflects its surroundings
* Create a class to store reflection properties

## Result:
![](/04-Reflection/tracer/image.bmp)

## Implementation:
* The first thing I want to do is create a ReflectionProperties class. At the moment, I have the diffuse and specular multipliers and the specular exponent hard coded into the trace method. I’m about to add another shading component that will have yet another multiplier so it’s about time to consolidate these multipliers into a class. Plus, each shape in the scene needs to be able to specify its own multipliers. This combined with a color (or later on a texture) is what will define what type of material the surface looks like. So the ReflectionProperties class will hold the multipliers, the specular exponent, and the color. 

A reflection properties instance will be constructed with four coefficients and a color. Each shape will need to be constructed with a ReflectionProperties instance that will define what it looks like. 
```cpp
// color, diffuse mult, specular mult, specular exp, reflective mult, light intensity 
SurfaceProperties surface{ GREY, 0.3f, 1.0f, 100.f, 0.9f, 0.f }; 
```
This will make the construction of each shape pretty ugly.
```cpp
// position, surface properties, radius
Sphere sphere3{ vec{2.5f, -1.f, -1.f}, SurfaceProperties{ PURPLE, 0.5f, 0.7f, 100.f, 0.1f, 0.f }, 0.5f };
```
 This definitely opens the door for factory methods to make shape building more readable. I’ll tackle that in the next project. For now, I’m going to prebuild some materials to include in the construction of shapes: a dull green surface, a shiny purple surface, and a mirror-like surface. 
```cpp
const SurfaceProperties BRIGHT{ PURPLE, 0.5f, 0.7f, 100.f, 0.1f, 0.f };
```
Now I can build shapes like this:
```cpp
// position, surface properties, radius
Sphere sphere3{ vec{2.5f, -1.f, -1.f}, BRIGHT, 0.5f };
```

* I want any surface to be able to emit light so I also added a “light intensity” member to the ReflectionProperties class. Now I can get rid of the isLightSource Boolean in the Shape class. I’ll use the light intensity to initialize final color produced by a shape.  This will make it appear at full intensity if it is in view of the camera. 
```cpp
final_color = pNearestShape->properties.color * pNearestShape->properties.intensity;
final_color += ambient + diffuse + etc…..;
```
The intensity will also be used as a multiplier for the diffuse and specular equations. This allows me to tune how much light a shape generates but, for now they are still treated as a point light source. 
```cpp
       float diffuse_light_intensity = std::max(0.f, nearestReflection->norm.dot(lightDir)) * secondary_shape.properties.intensity;
        float specular_light_intensity = std::powf(std::max(0.f, (-reflect(-lightDir, nearestReflection->norm)).dot(primary_ray.dir)), pNearestShape->properties.specular_exp) * secondary_shape.properties.intensity;
```

* Now to add reflection. This is actually pretty easy. First I create a recursive helper function that calculates the color at the origin of the incident ray. The base condition occurs when the ray does not collide with any shapes in the scene. In that case, it will return BLACK which is the zero Color and each stack frame will add its color contribution to the total color. This whole thing is really just a recursive sum function. 
```cpp
Color trace(const std::vector<Sphere>& shapes, const Ray& incidentRay, int depth, const Sphere* curShape);
```
I had to add two book keeping items I had to add to the function:

Int depth: tracks how deep the recursive stack is. At some point, I will want to raytrace inside a room or within a closed surface. In that case, we need to be able to specify a maximum number of collisions. This is an additional base case in the recursive function. 
```cpp
Color RayTracer::trace(const std::vector<Sphere>& shapes, const Ray& incidentRay, int depth, const Sphere* curShape) {
  if (depth >= max_depth) { // recursive base case
    return BLACK;
  }
  // remaining raytracer code
}
```
Sphere* curShape: the raytracer iterates through all the shapes in the scene and detects collisions. The current Shape is a pointer to the shape that is generating the incident ray. I pass it to the next recursive call so that it will be skipped when iterating through all the other shapes. 
```cpp
Color RayTracer::trace(const std::vector<Sphere>& shapes, const Ray& incidentRay, int depth, const Sphere* curShape) {
 for (auto& shape : shapes) {
    if (&shape != curShape) { // don’t trace the current shape
      // do stuff
    }
  }
}
```

* so everything seems to be working fine until I put one sphere behind another. Depending on what order I add them to the std::vector, the one in the back may be drawn on top of the one in front. I need to add something to my trace() method that makes sure rays collide with only the nearest object. This involves splitting the trace() method into two sections. 

In the first section, we loop through every shape in the scene....  keep typing stuff.... blah blah blahh

