#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
  public:
    glm::vec3 pos, dir; // pos is the base, dir is the direction
    float t_min, t_max;
};

#endif
