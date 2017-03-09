#include "Camera.h"
#include <FreeImage.h>

class Film {
  FIBITMAP * bitmap;

  public:
    Film();
    void commit(Sample & sample, RGBQUAD & color);
    void writeImage();
};
