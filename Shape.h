#ifndef SHAPE_H
#define SHAPE_H

#include "Intersection.h"
#include "Ray.h"
#include <glm/glm.hpp>

class Shape {
  public:
    glm::mat4 transform;
    bool hasTransform;

    float shininess;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 emission;
    glm::vec3 specular;

    Shape(bool transf);
    virtual bool intersect(Ray& ray, float * thit, Intersection * in) {return false;};
    virtual void transform_ray(Ray * ray);
    virtual void restore_ray(Ray * ray_to_restore, Ray * original_ray);
    virtual void local_to_world_t(float * thit, Ray * transf_ray, Ray * orig_ray, float transf_t);
    virtual void local_to_world_normal(glm::vec3 * world_normal, glm::vec3 normal);
    virtual glm::vec3 getFragColor();
};

class Triangle : public Shape {

  public:
    Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);
    virtual bool intersect(Ray& ray, float * thit, Intersection * in);

  protected:
    glm::vec3 v1, v2, v3;

};

class Sphere : public Shape {
  public:
    Sphere(glm::vec3 c, float r);
    virtual bool intersect(Ray& ray, float * thit, Intersection * in);

  protected:
    glm::vec3 center;
    float radius;
};

#endif
