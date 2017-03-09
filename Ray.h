#include "Point.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Ray {
  public:
    Point pos;
    glm::vec3 dir;
    float t_min, t_max;
};
