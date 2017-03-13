#include "Camera.h"
#include "variables.h"
#include <iostream>

Camera::Camera() : eye(0), fov(0), w(0), u(0), v(0) {};

Camera::Camera(glm::vec3 e, glm::vec3 c, glm::vec3 up, float f) {

  eye = e;
  fov = f;

  w = glm::normalize(e - c);
  u = glm::normalize(glm::cross(up, w));
  v = glm::cross(w, u);

}

void Camera::generateRay(Sample& sample, Ray * ray) {

  // Need to convert fov to radians before you use glm trig functions
  float fov_radians = fov * PI / 180;
  float fovy_calc = glm::tan(fov_radians / 2);
  float fovx_calc = fovy_calc * width / height; // multiply to make world aspect ratio 1:1

  // Generate ray direction increments
  float alpha = fovx_calc * ((sample.midx - (width/2)) / (width /2));
  float beta = fovy_calc * ((sample.midy - (height/2)) / (height/2));

  ray->dir = glm::normalize((alpha * u) + (beta * v) - w);
  ray->pos = eye;

}
