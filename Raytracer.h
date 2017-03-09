#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Camera.h"
#include <FreeImage.h>

class Scene;

extern Scene * scene;

class Raytracer {

  public:
    void trace(Ray& ray, int depth, RGBQUAD * color);
};

#endif
