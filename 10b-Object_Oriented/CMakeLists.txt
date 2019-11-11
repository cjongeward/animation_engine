cmake_minimum_required(VERSION 3.15)
project(10b_Object_Oriented)

set(CMAKE_CXX_STANDARD 17)

include_directories(tracer)

add_executable(10b_Object_Oriented
        tracer/ArrToBmp.h
        tracer/Color.h
        tracer/main.cpp
        tracer/MeshReader.h
        tracer/RayGenerator.cpp
        tracer/RayGenerator.h
        tracer/RayTracer.cpp
        tracer/RayTracer.h
        tracer/Reflection.h
        tracer/Scene.cpp
        tracer/Scene.h
        tracer/Settings.h
        tracer/Shapes.cpp
        tracer/Shapes.h
        tracer/SurfaceProperties.h
        tracer/TextureManager.h
        tracer/vec.cpp
        tracer/vec.h)
