#include "Film.h"
#include "variables.h"

Film::Film() {

  bitmap = FreeImage_Allocate(width, height, bits_per_pixel);
}

void Film::commit(Sample& sample, RGBQUAD& color) {

  FreeImage_SetPixelColor(bitmap, sample.x, sample.y, &color);

}

void Film::writeImage() {

  FreeImage_Save(FIF_PNG, bitmap, "test1.png", 0);

}
