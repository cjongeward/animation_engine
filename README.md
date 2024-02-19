# Ray Tracer
This is my ray tracer project. I have split it up into sub-projects that each aim to accomplish a specific goal and build off of the previous sub-project. The output for each project is a bitmap file which are all displayed below. 

## Projects
| Description   | Result   
|---|---
| [1 Basic Ray Tracer](1-Basic_Ray_Tracer/README.md): The most basic possible ray tracer. It looks like a circle but I swear it’s a sphere.    | ![](/1-Basic_Ray_Tracer/tracer/image.bmp)    
| [2 Sphere with diffuse shading](2-Diffuse_Lighting/README.md): Add some simple lighting to make the sphere actually look like a sphere.    | ![](/2-Diffuse_Lighting/tracer/image.bmp)    
[3 Sphere with specular shading](3-Specular_Lighting/README.md): Make the sphere shiny.    | ![](/3-Specular_Lighting/tracer/image.bmp)    
[4 Spheres with Reflection](04-Reflection/README.md): Trace rays through sequential collisions to simulate reflection and make a mirror ball.    | ![](/04-Reflection/tracer/image.bmp)    
[5 Shapes](05-Shapes/README.md): Add triangles and rectangles to the pool of shapes.    | ![](/05-Shapes/tracer/image.bmp)     
[6 Perspective viewing](06-Perspective/README.md): Implement perspective projection.  Wrap my image with a floor, ceiling, walls, and a mirror on the wall.    | ![](/06-Perspective/tracer/image.bmp)    
 [7 Design review and performance analysis](07-Perf_and_design/README.md): This program has gotten a bit slow. It takes 12 seconds to produce the previous image. This sub-project is a refactoring to improve the design and performance.    | :).    
[8 Shadows and Anti-aliasing](08-Shadows_Antialiasing/README.md):  Add shadows and antialiasing to smooth out the edges  | ![](/08-Shadows_Antialiasing/tracer/image.bmp)    
[9 Tranformations, Textures, Meshes](09-Textures_Transforms/README.md): A Texture Manager, Mesh reader, Transformation operator, and a big glass bunny   | ![](/09-Textures_Transforms/image.bmp) 
[10 lighting and decorating](RayTracer/README.md): Add lighting effects, decorate the room, parallelizing on the cpu, create composite shapes with bounding volumes  | ![](/RayTracer/image.bmp) 

TODOs possibly:

* [color clamping]
* [ambient occlusion]
* [stereoscopic shading]
* [parallelizing on gpu]
* [textures]
* [bump maps]
* [composite shapes]
* [making a video]
* [animating with a predefined path]
* [animating with a physics engine]
