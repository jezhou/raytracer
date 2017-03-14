#include "Shape.h"
#include <iostream>

using namespace glm;

Shape::Shape(bool transf) : hasTransform(false) {};

void Shape::transform_ray(Ray * ray) {

  // Instead of apply the transform to an object, apply the inverse transform to
  // the ray and it will have the same effect

  if(hasTransform) {
    mat4 inverse_matrix = inverse(transform);
    vec4 trans_ray_dir = inverse_matrix * vec4(ray->dir, 0.0);
    vec4 trans_ray_pos = inverse_matrix * vec4(ray->pos, 1.0);
    float w = trans_ray_pos.w;
    ray->dir = glm::normalize(vec3(trans_ray_dir));
    ray->pos = vec3(trans_ray_pos) / trans_ray_pos.w;
  }
}

void Shape::restore_ray(Ray * ray_to_restore, Ray * orig_ray) {

  // The transformed ray needs to be restored afterwards so the transformations
  // don't propagate on the same ray with mulitple transformed objects in a
  // scene

  ray_to_restore->dir = orig_ray->dir;
  ray_to_restore->pos = orig_ray->pos;
}

void Shape::local_to_world_t(float * thit, Ray * transf_ray, Ray * orig_ray, float transf_t) {

  // Because transformations are done in local object coordinates, the value
  // of thit is technically wrong. If a transform is done, whatever t is
  // needs to be retransformed back by transforming p, then getting the
  // distance between the original ray and p.

  vec3 p = transf_ray->pos + transf_t * transf_ray->dir;
  vec4 real_p = transform * vec4(p, 1.0);
  float w = real_p.w;
  vec3 dehomo_real_p = vec3(real_p.x / w, real_p.y / w, real_p.z / w);
  (*thit) = glm::length(orig_ray->pos - dehomo_real_p);

}

Triangle::Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3) :
  v1(vertex1), v2(vertex2), v3(vertex3), Shape(false) {}

// Basically, see if the ray intersects with the plane first.
// If it does, check if it's between the triangle bounds.
bool Triangle::intersect(Ray& ray, float * thit) {

  // Transform the ray instead of the object to calculate unique transform intersections
  Ray original_ray = Ray();
  original_ray.pos = ray.pos;
  original_ray.dir = ray.dir;
  Shape::transform_ray(&ray);

  // Calculate the plane normal
  glm::vec3 vector1, vector2;
  vector1 = glm::vec3(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
  vector2 = glm::vec3(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
  glm::vec3 normal = glm::normalize(glm::cross(vector2, vector1));

  // calculate t, the magnitude of how far the ray should go to get the point on the plane
  float t = glm::dot(v1 - ray.pos, normal) / glm::dot(ray.dir, normal);

  // if t >= 0, t is going in the right direction
  if (t >= 0) {

    // Use cramer's rule to find the barycentric coordinates of the triangle.
    // Skip finding alpha because alpha + beta + gamma = 1
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
    if (beta < 0 || beta > 1 || gamma < 0 || gamma > 1 || beta + gamma > 1) {
      // At this point, calculations are done. Restore to original ray.
      Shape::restore_ray(&ray, &original_ray);
      return false;
    }

    Shape::local_to_world_t(thit, &ray, &original_ray, t);
    Shape::restore_ray(&ray, &original_ray);

    return true;

  }

  // At this point, calculations are done. Restore to original ray.
  Shape::restore_ray(&ray, &original_ray);
  return false;

}

Sphere::Sphere(glm::vec3 c, float r) : center(c), radius(r), Shape(false) {}

bool Sphere::intersect(Ray & ray, float * thit) {

  // Transform the ray instead of the object to calculate unique transform
  // intersections. Make sure to save the original ray to restore afterwards
  Ray original_ray = Ray();
  original_ray.pos = ray.pos;
  original_ray.dir = ray.dir;
  Shape::transform_ray(&ray);

  glm::vec3 dir = ray.dir;
  glm::vec3 eye = ray.pos;

  float dis = pow(dot(dir, eye - center), 2) - dot(dir, dir) * (dot(eye-center, eye-center) - pow(radius, 2));

  if(dis >= 0) {
    float t1 = glm::dot(-dir, eye - center) + glm::sqrt(dis) / glm::dot(dir, dir);
    float t2 = glm::dot(-dir, eye - center) - glm::sqrt(dis) / glm::dot(dir, dir);


    // point grazes the edge of sphere, returning t1 or t2 is ok
    if (t1 == t2) {
      (*thit) = t1;
    }

    // If this point is reached, there are two intersection points. Pick the
    // smaller t value, because it means it's the one that's closer to the camera.
    // However, make sure the t value isn't negative
    else if (t1 < 0 && t2 < 0) {
      Shape::restore_ray(&ray, &original_ray);
      return false;
    }
    else if(t1 < 0) (*thit) = t2;
    else if(t2 < 0) (*thit) = t1;
    else {
      float closer = t1 < t2 ? t1 : t2;
      (*thit) = closer;
    }

    Shape::local_to_world_t(thit, &ray, &original_ray, *thit);
    Shape::restore_ray(&ray, &original_ray);

    return true;

  }

  Shape::restore_ray(&ray, &original_ray);

  // Discriminant is negative; roots are complex, no intersection at all
  return false;


}
