# Ray Tracer - Animation Engine
This is my ray tracer project. I have split it up into sub-projects that each aim to accomplish a specific goal and build off of the previous sub-project. The output for each project is a bitmap file which are all displayed below. At the moment, all the sub-projects are built with Visual Studio 2017 using the latest C++ standard and have no dependencies. 

## Projects
| Description   | Result   
|---|---
| [1 Basic Ray Tracer](1-Basic_Ray_Tracer/README.md): The most basic possible ray tracer. It looks like a circle but I swear it’s a sphere.    | ![](/1-Basic_Ray_Tracer/tracer/image.bmp)    
| [2 Sphere with diffuse shading](2-Diffuse_Lighting/README.md): Add some simple lighting to make the sphere actually look like a sphere.    | ![](/2-Diffuse_Lighting/tracer/image.bmp)    
[3 Sphere with specular shading](3-Specular_Lighting/README.md): Make the sphere shiny.    | ![](/3-Specular_Lighting/tracer/image.bmp)    
[4 Spheres with Reflection](04-Reflection/README.md): Trace rays through sequential collisions to simulate reflection and make a mirror ball.    | ![](/04-Reflection/tracer/image.bmp)    
[5 Shapes](05-Shapes/README.md): There’s only so much we can do with spheres. In this project, I add some triangles and rectangles to the image.    | ![](/05-Shapes/tracer/image.bmp)     
[6 Perspective viewing](06-Perspective/README.md): Up until now I’ve used orthographic projection which is fine, but won’t look realistic. Now I’ll implement perspective projection and wrap my image with a floor, ceiling, and walls. And let’s put a mirror on the wall just for fun.    | ![](/06-Perspective/tracer/image.bmp)    
 [7 Design review and performance analysis](07-Design_and_perf/README.md): This program has gotten a bit slow. It takes 12 seconds to produce the previous image. In this project, I’ll take a break and review the design so far. Then I’ll go through and make some performance optimizations to speed this thing up.    | class diagram here.    
[8 Shadows and Anti-aliasing](08-Shadows_Antialiasing/README.md):    | ![](/08-Shadows_Antialiasing/tracer/image.bmp)    

Coming soon

* [color clamping]
* [rotations]
* [ambient occlusion]
* [stereoscopic shading]
* [parallelizing]
* [textures]
* [bump maps]
* [meshes]
* [composite shapes]
* [making a video]
* [animating with a predefined path]
* [animating with a physics engine]
* [running in real time]
