#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "Sampler.h"
#include "Shape.h"

#define PI 3.14159

class Camera {

  float fov;
  glm::vec3 eye;
  glm::vec3 w, u, v;
  glm::mat4 camera;

public:
  Camera();
  Camera(glm::vec3 e, glm::vec3 c, glm::vec3 up, float f);
  void generateRay(Sample& sample, Ray* ray);
};

#endif
