class BVHNode {
public:
  glm::vec3 bounds;
  BVHNode * left;
  BVHNode * right;
  Shape * shape; // will be blank unless it's a child node

  void calculate_bounds();
  bool intersect(Ray * ray);
}
