#include "Sampler.h"
#include <vector>

class Scene {

  std::vector<Shape *> * shapes;

public:
  Scene();
  void render();
  void addShape(Shape * shape);
  std::vector<Shape*> * getShapes();

};
