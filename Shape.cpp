#include "Shape.h"
#include <iostream>

Triangle::Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3) :
  v1(vertex1), v2(vertex2), v3(vertex3) {}

// Basically, see if the ray intersects with the plane first.
// If it does, check if it's between the triangle bounds.
bool Triangle::intersect(Ray& ray) {

  // Using the plane intersection equation
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection

  // Calculate the plane normal
  glm::vec3 vector1, vector2, plane_normal_base;
  plane_normal_base = v1;
  vector1 = glm::vec3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
  vector2 = glm::vec3(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
  glm::vec3 normal = glm::normalize(glm::cross(vector2, vector1));

  // calculate denom
  float denom = glm::dot(ray.dir, normal);

  if(denom > 1e-6) {
    float t = glm::dot(v1 - ray.pos, normal) / denom;

    if (t >= 0) {
      // intersection point, in which the ray hits the PLANE, not the triangle
      glm::vec3 p = ray.pos + ray.dir * t;

      // using algorithm in pg 49 of shirley textbook
      glm::vec3 na = glm::cross(v3-v2, p-v2);
      glm::vec3 nb = glm::cross(v1-v3, p-v3);
      glm::vec3 nc = glm::cross(v2-v1, p-v1);

      float nlsq = std::pow(glm::length(normal), 2);

      float alpha = glm::dot(normal, na) / nlsq;
      float beta = glm::dot(normal, nb) / nlsq;
      float gamma = 1 - alpha - beta;

      return alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1;
    }

  }

  return false;

}
