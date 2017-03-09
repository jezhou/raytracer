#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include "Scene.h"
using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define BITS_PER_PIXEL 24 // 3 8-bit rgb values = 24

Scene * scene;

int main(int argc, char* argv[]) {

  // TODO: Uncomment this out later
  // if (argc < 2) {
  //   cerr << "Usage: raytracer <scenefile>\n";
  //   exit(-1);
  // }

  FreeImage_Initialise();
  scene = new Scene();
  scene->render();

  FreeImage_DeInitialise();
}
