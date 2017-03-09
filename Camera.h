#include <glm/glm.hpp>
#include "Sample.h"
#include "Ray.h"

class Camera {

  float fov;
  glm::vec3 eye;
  glm::vec3 w, u, v;
  glm::mat4 camera;

public:
  Camera(glm::vec3 e, glm::vec3 c, glm::vec3 up, float f);
  void generateRay(Sample& sample, Ray* ray);
};
