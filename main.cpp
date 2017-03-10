#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include "Scene.h"
using namespace std;

#define MAINPROGRAM
#include "variables.h"

void init() {
  width = 800;
  height = 600;
  bits_per_pixel = 24;
}

int main(int argc, char* argv[]) {

  // TODO: Uncomment this out later
  // if (argc < 2) {
  //   cerr << "Usage: raytracer <scenefile>\n";
  //   exit(-1);
  // }

  FreeImage_Initialise();
  init();
  scene = Scene();
  scene.render();
  FreeImage_DeInitialise();
}
