#include "Light.h"

Light::Light(float x, float y, float z, float w, float r, float g, float b) {
  props.x = x;
  props.y = y;
  props.z = z;
  props.w = w;
  color.r = r;
  color.g = g;
  color.b = b;
}
