#include "Raytracer.h"
#include <vector>
#include <cfloat>
#include <iostream>

void Raytracer::trace(Ray& ray, int depth, RGBQUAD * color) {

  float thit;
  float smallest_thit = FLT_MAX;
  bool hit_at_least_once = false;
  LocalGeo in;

  std::vector<Shape*>::iterator it = shapes.begin();
  std::vector<Shape*>::iterator end = shapes.end();
  Shape * closestObject;
  Shape * currentObject;

  bool hit = false;
  for(; it != end; it++) {
    if (depth > 5) {
      color->rgbRed = 0;
      color->rgbGreen = 0;
      color->rgbBlue = 0;
    }

    hit = (*it)->intersect(ray, &thit);
    if(hit && thit < smallest_thit && thit >= 0) {
      hit_at_least_once = true;
      smallest_thit = thit;
      closestObject = *it;
    }

  }

  // TODO: return proper shading in the future
  //       right now this will just color in whatever green
  if(hit_at_least_once && dynamic_cast<Triangle*>(closestObject)) {
    color->rgbGreen = 255;
    color->rgbRed = 0;
    color->rgbBlue = 0;
  } else if (hit_at_least_once) {
    color->rgbGreen = 255;
    color->rgbRed = 255;
    color->rgbBlue = 255;
  } else {
    color->rgbGreen = 0;
    color->rgbRed = 0;
    color->rgbBlue = 0;
  }

}
