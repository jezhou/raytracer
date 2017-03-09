#ifndef SCENE_H
#define SCENE_H

#include "Sampler.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Film.h"
#include <vector>

class Scene {

  std::vector<Shape *> * shapes;

public:
  Scene();
  void render();
  void addShape(Shape * shape);
  std::vector<Shape*> * getShapes();

};

#endif
