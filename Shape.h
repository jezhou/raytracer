#ifndef SHAPE_H
#define SHAPE_H

#include "LocalGeo.h"
#include <glm/glm.hpp>

class Shape {

  public:
    bool intersect(Ray& ray);
    bool intersectP(Ray& ray);
};

class Triangle : public Shape {

  public:
    Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);
    bool intersect(Ray& ray);

  protected:
    glm::vec3 v1, v2, v3;

};

#endif
