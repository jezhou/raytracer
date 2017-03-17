#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {

public:
  Light(float x, float y, float z, float w, float r, float g, float b);
  glm::vec3 color;
  glm::vec3 attenuation_terms;
  glm::vec4 props;
};

#endif
