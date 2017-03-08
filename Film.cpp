#include "Film.h"

Film::Film() {

  // TODO: Change bc hardcoded
  float WIDTH = 100;
  float HEIGHT = 100;
  float BITS_PER_PIXEL = 24;


  bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BITS_PER_PIXEL);
}

void Film::commit(Sample& sample, RGBQUAD& color) {

  FreeImage_SetPixelColor(bitmap, sample.x, sample.y, &color);

}

void Film::writeImage() {

  FreeImage_Save(FIF_PNG, bitmap, "test1.png", 0);

}
