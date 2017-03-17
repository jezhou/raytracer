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

  char result[100];

  std::strcpy(result, outputfilename);
  std::strcat(result, ".png");

  cout << "Done! Saving to " << result << endl;
  FreeImage_Save(FIF_PNG, bitmap, result, 0);

}
