#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include <FreeImage.h>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: raytracer <scenefile>\n";
    exit(-1);
  }
  
  FreeImage_Initialise();

  FreeImage_DeInitialise();
}
