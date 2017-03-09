#ifndef LOCALGEO_H
#define LOCALGEO_H

#include <glm/glm.hpp>
#include "Ray.h"

class LocalGeo {
public:
  Point pos;
  glm::vec3 normal;
};

#endif
