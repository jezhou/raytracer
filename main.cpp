#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include <FreeImage.h>
using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define BITS_PER_PIXEL 24 // 3 8-bit rgb values = 24

int main(int argc, char* argv[]) {

  // TODO: Uncomment this out later
  // if (argc < 2) {
  //   cerr << "Usage: raytracer <scenefile>\n";
  //   exit(-1);
  // }

  FreeImage_Initialise();
  FIBITMAP * bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BITS_PER_PIXEL);
  RGBQUAD color;

  for(int i = 0; i < WIDTH; i++) {
    for(int j = 0; j< HEIGHT; j++) {
      color.rgbRed = 0;
      color.rgbGreen = (double)i / WIDTH * 255;
      color.rgbBlue = (double)j / HEIGHT;
      FreeImage_SetPixelColor(bitmap, i, j, &color);
    }
  }

  FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
  FreeImage_DeInitialise();
}
