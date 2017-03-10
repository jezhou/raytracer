#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <FreeImage.h>
#include "Ray.h"
#include "Shape.h"

class Scene;

class Raytracer {

  public:
    void trace(Ray& ray, int depth, RGBQUAD * color);
};

#endif
