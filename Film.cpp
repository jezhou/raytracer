#include "Film.h"
#include "variables.h"
#include <string>
#include <iostream>

using namespace std;

Film::Film() {

  bitmap = FreeImage_Allocate(width, height, bits_per_pixel);
}

void Film::commit(Sample& sample, RGBQUAD& color) {

  FreeImage_SetPixelColor(bitmap, sample.x, sample.y, &color);

}

void Film::writeImage() {

  FreeImage_Save(FIF_PNG, bitmap, outputfilename.c_str(), 0);
  cout << "Done writing image! Saving to " << outputfilename << endl;

}
