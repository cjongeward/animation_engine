cmake_minimum_required(VERSION 3.15)
project(10d_Object_Oriented)

set(CMAKE_CXX_STANDARD 17)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg -g")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
#SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

include_directories(tracer)

add_executable(10d_Object_Oriented
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
