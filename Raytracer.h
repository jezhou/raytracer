#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <FreeImage.h>
#include <glm/glm.hpp>
#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"
#include "variables.h"

using namespace glm;

class Scene;

class Raytracer {

  public:
    void trace(Ray * ray, int depth, glm::vec3 * retlight);
    glm::vec3 compute_light(Intersection * in, Shape * closestObject, Ray * ray, int depth);
};

#endif
