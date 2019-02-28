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
bitmap generating code:  


