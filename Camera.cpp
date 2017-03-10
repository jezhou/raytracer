#include "Camera.h"
#include "variables.h"
#include <iostream>

Camera::Camera(glm::vec3 e, glm::vec3 c, glm::vec3 up, float f) {

  eye = e;
  fov = f;

  w = glm::normalize(e - c);
  u = glm::normalize(glm::cross(up, w));
  v = glm::cross(w, u);

}

void Camera::generateRay(Sample& sample, Ray * ray) {

  float fovy_calc = glm::tan(fov/2);
  float fovx_calc = fovy_calc * width/height;

  float alpha = fovy_calc * ((sample.x - (width / 2)) / (width /2));
  float beta = fovx_calc * (((height/2) - sample.y) / (height/2));

  ray->dir = glm::normalize(alpha * u + beta * v - w);;
  ray->pos = eye;

}
