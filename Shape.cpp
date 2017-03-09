#include "Shape.h"

Triangle::Triangle(Point vertex1, Point vertex2, Point vertex3) :
  v1(vertex1), v2(vertex2), v3(vertex3) {}

// Basically, see if the ray intersects with the plane first.
// If it does, check if it's between the triangle bounds.
bool Triangle::intersect(Ray& ray, float* thit, LocalGeo* local) {

  // Calculate the plane normal
  glm::vec3 vector1, vector2, plane_normal, plane_normal_base;
  plane_normal_base = glm::vec3(v1.px, v1.py, v1.pz);
  vector1 = glm::vec3(v1.px - v2.px, v1.py - v2.py, v1.pz - v2.pz);
  vector2 = glm::vec3(v1.px - v3.px, v1.py - v3.py, v1.pz - v3.pz);

  plane_normal = glm::normalize(glm::cross(vector1, vector2));

  glm::vec3 ray_origin = glm::vec3(ray.pos.px, ray.pos.py, ray.pos.pz);
  glm::vec3 ray_direction = ray.dir;

  float denom = glm::dot(plane_normal, ray_direction);
  if(denom > 1e-6) {
    glm::vec3 temp = ray_origin - plane_normal_base;
    float temp2 = glm::dot(temp, plane_normal);
    thit = &temp2;
    return (*thit >= 0);
  }

  return false;

}
