#ifndef SHAPE_H
#define SHAPE_H

#include "LocalGeo.h"
#include <glm/glm.hpp>

class Shape {
  public:
    virtual bool intersect(Ray& ray, float * thit) { return false;};
};

class Triangle : public Shape {

  public:
    Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);
    virtual bool intersect(Ray& ray, float * thit);

  protected:
    glm::vec3 v1, v2, v3;

};

class Sphere : public Shape {

};

#endif
