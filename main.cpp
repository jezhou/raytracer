#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include "Scene.h"
#include "readfile.h"

#define MAINPROGRAM
#include "variables.h"

using namespace std;
using namespace glm;

void init() {
  bits_per_pixel = 24;
}

int main(int argc, char* argv[]) {

  if(argc != 2) {
    cerr << "Usage: ./raytracer <scene_file>\n";
    return 2;
  }

  FreeImage_Initialise();
  init();
  readfile(argv[1]);

  // Acceleration structure


  scene = Scene();
  scene.render();

  FreeImage_DeInitialise();
}
