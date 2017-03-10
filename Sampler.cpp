#include "Sampler.h"

Sampler::Sampler(float x, float y) : width(x), height(y), cur_x(0), cur_y(0) {};

bool Sampler::getSample(Sample * sample) {

  // Set the sample values
  sample->x = cur_x;
  sample->y = cur_y;
  sample->midx = cur_x + 0.5;
  sample->midy = cur_y + 0.5;

  if(cur_x == width - 1) {
    cur_x = -1;
    cur_y++;
  }

  if(cur_y == height) {
    return false;
  }

  cur_x++;
  return true;

}
