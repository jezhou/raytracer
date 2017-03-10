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
  width = 640;
  height = 480;
  bits_per_pixel = 24;
}

int main(int argc, char* argv[]) {
  FreeImage_Initialise();
  init();
  scene = Scene();
  scene.render();
  FreeImage_DeInitialise();
}
