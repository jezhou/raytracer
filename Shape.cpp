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
  plane_normal_base = glm::vec3(v1.x, v1.y, v1.z);
  vector1 = glm::vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
  vector2 = glm::vec3(v1.x - v3.x, v1.y - v3.y, v1.z - v3.z);

  glm::vec3 normal = glm::cross(vector1, vector2);

  float denom = glm::dot(normal, ray.dir);
  if(denom > 1e-6) {
    glm::vec3 temp = ray.pos - plane_normal_base;
    float t = glm::dot(temp, normal);
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
      float gamma = glm::dot(normal, nc) / nlsq;

      // std::cout << "denom ";
      // std::cout << denom;
      // std::cout << " t ";
      // std::cout << t;
      // std::cout << " p ";
      // std::cout << p.x;
      // std::cout << " ";
      // std::cout << p.y;
      // std::cout << " ";
      // std::cout << p.z;
      // std::cout << " ";
      // std::cout << " nlsq ";
      // std::cout << nlsq;
      // std::cout << " alpha ";
      // std::cout << alpha;
      // std::cout << " beta ";
      // std::cout << beta;
      // std::cout << " gamma ";
      // std::cout << gamma;
      // std::cout << "\n";

      return alpha > 0 && alpha < 1 &&
        beta > 0 && beta < 1 &&
        gamma > 0 && gamma < 1;

    };
  }

  return false;

}
