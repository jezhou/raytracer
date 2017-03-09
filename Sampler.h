#ifndef SAMPLER_H
#define SAMPLER_H

#include "Film.h"

class Sampler {

  float cur_x, cur_y;
  float height, width;

  public:
    Sampler(float x, float y);
    bool getSample(Sample * sample);
};

#endif
