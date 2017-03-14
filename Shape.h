#ifndef SHAPE_H
#define SHAPE_H

#include "LocalGeo.h"
#include <glm/glm.hpp>

class Shape {
  public:
    glm::mat4 transform;
    bool hasTransform;
    float ambient;
    float diffuse;
    float shininess;
    float emission;
    float specular;

    Shape(bool transf);
    virtual bool intersect(Ray& ray, float * thit) { return false;};
    virtual void transform_ray(Ray * ray);
    virtual void restore_ray(Ray * ray_to_restore, Ray * original_ray);
    virtual void local_to_world_t(float * thit, Ray * transf_ray, Ray * orig_ray, float transf_t);
};

class Triangle : public Shape {

  public:
    Triangle(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3);
    virtual bool intersect(Ray& ray, float * thit);

  protected:
    glm::vec3 v1, v2, v3;

};

class Sphere : public Shape {
  public:
    Sphere(glm::vec3 c, float r);
    virtual bool intersect(Ray& ray, float * thit);

  protected:
    glm::vec3 center;
    float radius;
};

#endif
