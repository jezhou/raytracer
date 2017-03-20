#include <vector>
#include <glm/glm.hpp>
#include <cmath>

#include "Ray.h"
#include "Shape.h"

using namespace glm;

class BVHNode {

  protected:
    Shape * shape; // will be blank unless it's a child node

  public:
    BVHNode();
    BVHNode(Shape * shape);
    BVHNode * left;
    BVHNode * right;
    glm::vec3 min_bounds;
    glm::vec3 max_bounds;

    void calculate_bounds();
    bool intersect(Ray * ray);
    static BVHNode * build_hierarchy(vector<Shape*> all_shapes);
}
