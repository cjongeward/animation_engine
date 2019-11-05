#ifndef MESHREADER_H_
#define MESHREADER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Shapes.h"
#include "vec.h"
#include "SurfaceProperties.h"

std::vector<std::unique_ptr<Shape>> parseMesh(std::string filename) {
  std::ifstream iStream{filename};

  std::string dontCare;
  iStream >> dontCare;

  int numPoints, numTris, numQuads;
  iStream >> numPoints >> numTris >> numQuads;

  std::vector<vec> points;
  for(int i = 0; i < numPoints; ++i) {
    float x, y, z;
    iStream >> x >> y >> z;
    points.emplace_back(x, y, z);
  }

  std::vector<std::unique_ptr<Shape>> tris;
  for(int i = 0; i < numTris; ++i) {
    int numVals, p1, p2, p3;
    iStream >> numVals >> p1 >> p2 >> p3;
    tris.push_back(std::make_unique<Triangle>(points[p1], points[p2], points[p3]));
  }

  return tris;
}


#endif
