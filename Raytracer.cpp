#include "Raytracer.h"
#include <vector>
#include <iostream>

void Raytracer::trace(Ray& ray, int depth, RGBQUAD * color) {

  float thit;
  LocalGeo in;

  //TODO: Remove after milestone
  glm::vec3 v0 = glm::vec3(-1, -1, 0);
  glm::vec3 v1 = glm::vec3(1, -1, 0);
  glm::vec3 v2 = glm::vec3(1, 1, 0);
  glm::vec3 v3 = glm::vec3(-1, 1, 0);
  Triangle triangle(v0, v1, v2);
  Triangle triangle2(v0, v2, v3);

  if (depth > 5) {
    color->rgbRed = 0;
    color->rgbGreen = 0;
    color->rgbBlue = 0;
    return;
  }

  // TODO: Update from milestone

  if (triangle.intersect(ray)) {
    color->rgbRed = 0;
    color->rgbGreen = 255;
    color->rgbBlue = 0;
  } else {
    color->rgbRed = 0;
    color->rgbGreen = 0;
    color->rgbBlue = 0;
  }

}
