#include "Shape.h"
#include <iostream>

Triangle::Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3) :
  v1(vertex1), v2(vertex2), v3(vertex3) {}

// Basically, see if the ray intersects with the plane first.
// If it does, check if it's between the triangle bounds.
bool Triangle::intersect(Ray& ray) {


  // Calculate the plane normal
  glm::vec3 vector1, vector2, plane_normal_base;
  vector1 = glm::vec3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
  vector2 = glm::vec3(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
  glm::vec3 normal = glm::normalize(glm::cross(vector2, vector1));

  // calculate t, the magnitude of how far the ray should go to get the point on the plane
  float t = glm::dot(v1 - ray.pos, normal) / glm::dot(ray.dir, normal);

  // if t >= 0, t is going in the right direction
  if (t >= 0) {

    // Use cramer's rule to find the barycentric coordinates of the triangle.
    // Skip finding alpha because alpha + beta + gamma = 0
    // See page 78 of the shirley textbook
    float A = glm::determinant(glm::mat3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z,
                                 v1.x - v3.x, v1.y - v3.y, v1.z - v3.z,
                                 ray.dir.x, ray.dir.y, ray.dir.z));

    float beta = glm::determinant(glm::mat3(v1.x - ray.pos.x, v1.y - ray.pos.y, v1.z - ray.pos.z,
                           v1.x - v3.x, v1.y - v3.y, v1.z - v3.z,
                           ray.dir.x, ray.dir.y, ray.dir.z)) / A;

    float gamma = glm::determinant(glm::mat3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z,
                          v1.x - ray.pos.x, v1.y - ray.pos.y, v1.z - ray.pos.z,
                          ray.dir.x, ray.dir.y, ray.dir.z)) / A;

    // If none of the below are true, the point is outside of the triangle and should return black pixel
    if (beta < 0 || beta > 1 || gamma < 0 || gamma > 1 || beta + gamma > 1) return false;

    return true;


  }

  return false;

}
