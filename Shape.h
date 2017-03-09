#ifndef SHAPE_H
#define SHAPE_H

#include "LocalGeo.h"

class Shape {

  public:
    bool intersect(Ray& ray, float* thit, LocalGeo* local);
    bool intersectP(Ray& ray);
};

class Triangle : public Shape {

  public:
    Triangle(Point vertex1, Point vertex2, Point vertex3);
    bool intersect(Ray& ray, float* thit, LocalGeo* local);

  protected:
    Point v1, v2, v3;

};

#endif
