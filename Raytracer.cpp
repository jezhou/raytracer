#include "Raytracer.h"
#include <vector>
#include <iostream>

typedef std::vector<Shape *>::iterator shape_iter;

void Raytracer::trace(Ray& ray, int depth, RGBQUAD * color) {

  float thit;
  LocalGeo in;

  //TODO: Remove after milestone
  Point v0(-1, -1, 0);
  Point v1(1, -1, 0);
  Point v2(1, 1, 0);
  Point v3(-1, 1, 0);
  Triangle triangle(v0, v1, v2);

  if (depth > 5) {
    color->rgbRed = 0;
    color->rgbGreen = 0;
    color->rgbBlue = 0;
    return;
  }

  // TODO: Update from milestone

  if (triangle.intersect(ray, &thit, &in)) {
    color->rgbRed = 0;
    color->rgbGreen = 255;
    color->rgbBlue = 0;
  } else {
    color->rgbRed = 0;
    color->rgbGreen = 0;
    color->rgbBlue = 0;
  }

}
