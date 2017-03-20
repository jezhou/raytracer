#include "BVHNode.h"

BVHNode::BVHNode() : shape(NULL), left(NULL), right(NULL), bounds(vec3(0, 0, 0)) {}
BVHNode::BVHNode(Shape * shape) : left(NULL), right(NULL), shape(shape), bounds(vec3(0, 0, 0)) {}

void BVHNode::calculate_bounds() {
  if(shape) {

    if(dynamic_cast<Triangle*>(shape)) {

      vec3 working_v1 = shape->v1;
      vec3 working_v2 = shape->v2;
      vec3 working_v3 = shape->v3;

      if(shape->hasTransform) {
        vec4 transf_v1 = shape->transform * vec4(shape->v1, 1);
        vec4 transf_v2 = shape->transform * vec4(shape->v2, 1);
        vec4 transf_v3 = shape->transform * vec4(shape->v3, 1);
        working_v1 = vec3(transf_v1) / transf_v1.w;
        working_v2 = vec3(transf_v2) / transf_v2.w;
        working_v3 = vec3(transf_v3) / transf_v3.w;
      }

      min_bounds.x = std::min(std::min(working_v1.x, working_v2.x), working_v3.x);
      max_bounds.x = std::max(std::max(working_v1.x, working_v2.x), working_v3.x);
      min_bounds.y = std::min(std::min(working_v1.y, working_v2.y), working_v3.y);
      max_bounds.y = std::max(std::max(working_v1.y, working_v2.y), working_v3.y);
      min_bounds.z = std::min(std::min(working_v1.z, working_v2.z), working_v3.z);
      max_bounds.z = std::max(std::max(working_v1.z, working_v2.z), working_v3.z);

    } else { // This is a sphere

      mat4 M = shape->transform;
      mat4 Mt = transpose(M);
      float r = sphere->radius;
      mat4 sphere_rep = mat4(r, 0, 0, 0, 0, r, 0, 0, 0, 0, r, 0, 0, 0, 0, -1);
      mat4 R = M * inverse(sphere_rep) * Mt;

      float divisor = R[3][3];

      min_bounds.x = R[0][3] - std::sqrt(std::pow(R[0][3], 2) - divisor * R[0][0]) / divisor;
      max_bounds.x = R[0][3] - std::sqrt(std::pow(R[0][3], 2) - divisor * R[0][0]) / divisor;
      min_bounds.y = R[1][3] - std::sqrt(std::pow(R[1][3], 2) - divisor * R[1][1]) / divisor;
      max_bounds.y = R[1][3] - std::sqrt(std::pow(R[1][3], 2) - divisor * R[1][1]) / divisor;
      min_bounds.z = R[2][3] - std::sqrt(std::pow(R[2][3], 2) - divisor * R[2][2]) / divisor;
      max_bounds.z = R[2][3] + std::sqrt(std::pow(R[2][3], 2) - divisor * R[2][2]) / divisor;

    }

  }
}

vec3 BVHNode::combine_bounds(BVHNode * left, BVHNode * right) {
  min_bounds.x = std::min(left->min_bounds.x, right->min_bounds.x);
  max_bounds.x = std::max(left->max_bounds.x, right->max_bounds.x);
  min_bounds.y = std::min(left->min_bounds.y, right->min_bounds.y);
  max_bounds.y = std::max(left->max_bounds.y, right->max_bounds.y);
  min_bounds.z = std::min(left->min_bounds.z, right->min_bounds.z);
  max_bounds.z = std::max(left->max_bounds.z, right->max_bounds.z);
}

bool BVHNode::intersect(Ray * ray) {
  
}

BVHNode * BVHNode::build_hierarchy(vector<Shape*> all_shapes) {

  std::vector<Shape*>::iterator sit = all_shapes.begin();
  std::vector<Shape*>::iterator send = all_shapes.end();
  std::vector<BVHNode*> bvh_leaves;

  // Create a BVHNode vector, basically wrapping all the shapes as BVH nodes
  for(; sit != send; sit++) {
    BVHNode * working = new BVHNode(*sit);
    working->calculate_bounds();
    bvh_leaves.push_back(working);
  }

  // Sort the BVHNode vector along a certain axis
  std::vector<BVHNode*>::iterator bit = bvh_leaves.begin();
  std::vector<BVHNode*>::iterator bend = bvh_leaves.end();
  std::sort(bit, bend, boundingSort);

  // Finally, send the BVHNode into the the recursive function. It is the overloaded
  // one that takes in a vector of BVHNodes ptrs. Return value is the root of tree
  return build_hierarchy(bvh_leaves);

}

BVHNode * BVHNode::build_hierarchy(vector<BVHNode*> bvh_leaves) {

  BVHNode * parent = new BVHNode();
  BVHNode * left, right;

  std::vector<BVHNode*>::iterator bit = bvh_leaves.begin();
  std::vector<BVHNode*>::iterator bend = bvh_leaves.end();
  std::vector<BVHNode*>::iterator halfway = bit + std::distance(bit, bend) / 2;

  if(bend - bit == 1) {
    delete parent;
    return *bit;
  } else if (bend - bit == 2) {
    left = *bit;
    right = *(bit + 1);
  } else {
    std::sort(bit, bend, boundingSort);
    left = build_hierarchy(bit, halfway);
    right = build_hierarchy(halfway, bend);
  }

  parent->left = left;
  parent->right = right;
  parent->bounds = combine_bounds(left, right);

  return parent;
}
