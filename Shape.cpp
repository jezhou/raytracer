#include "Shape.h"
#include <iostream>

using namespace glm;

Triangle::Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3) :
  v1(vertex1), v2(vertex2), v3(vertex3) {}

// Basically, see if the ray intersects with the plane first.
// If it does, check if it's between the triangle bounds.
bool Triangle::intersect(Ray& ray, float * thit) {

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

    (*thit) = t;

    return true;


  }

  return false;

}

Sphere::Sphere(glm::vec3 c, float r) : center(c), radius(r) {}

bool Sphere::intersect(Ray & ray, float * thit) {

  glm::vec3 dir = ray.dir;
  glm::vec3 eye = ray.pos;

  float dis = pow(dot(dir, eye - center), 2) - dot(dir, dir) * (dot(eye-center, eye-center) - pow(radius, 2));

  if(dis >= 0) {
    float t1 = glm::dot(-dir, eye - center) + glm::sqrt(dis) / glm::dot(dir, dir);
    float t2 = glm::dot(-dir, eye - center) - glm::sqrt(dis) / glm::dot(dir, dir);

    // point grazes the edge of sphere, returning t1 or t2 is ok
    if (t1 == t2) {
      thit = &t1;
      return true;
    }

    // If this point is reached, there are two intersection points. Pick the
    // smaller t value, because it means it's the one that's closer to the camera.
    // However, make sure the t value isn't negative

    if (t1 < 0 && t2 < 0) return false;
    else if(t1 < 0) thit = &t2;
    else if(t2 < 0) thit = &t1;
    else {
      float closer = t1 < t2 ? t1 : t2;
      (*thit) = closer;
    }

    return true;

  }

  // Discriminant is negative; roots are complex, no intersection at all
  return false;


}
