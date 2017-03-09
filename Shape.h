#include "Point.h"
#include "LocalGeo.h"

class Shape {

  public:
    bool intersect(Ray& ray, float* thit, LocalGeo* local);
    bool intersectP(Ray& ray);
}

class Triangle : public Shape {

  public:
    Point v1, v2, v3;

}
