#ifndef FILM_H
#define FILM_H

#include "Raytracer.h"
#include <FreeImage.h>

class Film {
  FIBITMAP * bitmap;

  public:
    Film();
    void commit(Sample & sample, RGBQUAD & color);
    void writeImage();
};

#endif
