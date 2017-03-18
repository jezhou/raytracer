/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/* NOTE: THIS HAS BEEN ADAPTED FROM HW2 TO HW4 BY JESSE AND YASY             */
/*****************************************************************************/

/*****************************************************************************/
// This file is readfile.cpp.  It includes helper functions for matrix
// transformations for a stack (matransform) and to rightmultiply the
// top of a stack.  These functions are given to aid in setting up the
// transformations properly, and to use glm functions in the right way.
// Their use is optional in your program.


// The functions readvals and readfile do basic parsing.  You can of course
// rewrite the parser as you wish, but we think this basic form might be
// useful to you.  It is a very simple parser.

// Please fill in parts that say YOUR CODE FOR HW 2 HERE.
// Read the other parts to get a context of what is going on.

/*****************************************************************************/

// Basic includes to get this file to work.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include "Shape.h"
#include "variables.h"
#include "readfile.h"
#include "Transforms.h"

using namespace glm;


// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, float * values)
{
  mat4 transform = transfstack.top();
  vec4 valvec = vec4(values[0],values[1],values[2],values[3]);
  vec4 newval = transform * valvec;
  for (int i = 0; i < 4; i++) values[i] = newval[i];
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack)
{
  mat4 &T = transfstack.top();
  T = T * M;
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.
bool readvals(stringstream &s, const int numvals, float* values)
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i];
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n";
      return false;
    }
  }
  return true;
}

void readfile(const char* filename)
{
  ambient = vec3();
  ambient.r = 0.2 * 255;
  ambient.g = 0.2 * 255;
  ambient.b = 0.2 * 255;
  attenuation = vec3(1, 0, 0);
  string str, cmd;
  ifstream in;
  in.open(filename);
  if (in.is_open()) {

    cout << "Reading in file " << filename << endl;
    outputfilename = string(filename) + ".png";

    // I need to implement a matrix stack to store transforms.
    // This is done using standard STL Templates
    stack <mat4> transfstack;
    transfstack.push(mat4(1.0));  // identity

    cerr << "Reading file... " << endl;

    getline (in, str);
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {

        stringstream s(str);
        s >> cmd;
        bool validinput;
        float values[10];

        if (cmd == "output") {
          string outfile;
          s >> outfile;
          if (s.fail()) {
            cout << "Output file name invalid. Leave the command blank as an alternative" << endl;
            break;
          }
          outputfilename = outfile;
        }
        else if(cmd == "camera") {
          validinput = readvals(s, 10, values);
          if(validinput) {
            camera = Camera(
                            glm::vec3(values[0], values[1], values[2]), // eye
                            glm::vec3(values[3], values[4], values[5]), // dest
                            glm::vec3(values[6], values[7], values[8]), // up
                            values[9] // fov
                          );
          }
        } else if(cmd == "size") {
          validinput = readvals(s,2,values);
          if(validinput) {
            width = (int) values[0];
            height = (int) values[1];
          }
        } else if (cmd == "vertex") {
          validinput = readvals(s,3,values);
          if(validinput) {
            vertices.push_back(glm::vec3(values[0], values[1], values[2]));
          }
        } else if (cmd == "tri") {
          validinput = readvals(s, 3, values);
          if(validinput) {
            Shape * tri = new Triangle(
              vertices.at(values[0]),
              vertices.at(values[1]),
              vertices.at(values[2])
            );
            tri->ambient = vec3(ambient);
            tri->emission = vec3(emission);
            tri->diffuse = vec3(diffuse);
            tri->specular = vec3(specular);
            tri->shininess = shininess;
            tri->transform = transfstack.top();
            tri->hasTransform = true;
            shapes.push_back(tri);
          }

        } else if (cmd == "sphere") {
          validinput = readvals(s, 4, values);
          if(validinput) {
            Shape * sphere = new Sphere(
              vec3(
                values[0],
                values[1],
                values[2]
              ),
              values[3]
            );
            sphere->ambient = vec3(ambient);
            sphere->emission = vec3(emission);
            sphere->diffuse = vec3(diffuse);
            sphere->specular = vec3(specular);
            sphere->shininess = shininess;
            sphere->transform = transfstack.top();
            sphere->hasTransform = true;
            shapes.push_back(sphere);
          }

        } else if (cmd == "attenuation") {
          if(readvals(s, 3, values)) {
            attenuation.x = values[0];
            attenuation.y = values[1];
            attenuation.z = values[2];
          }
        } else if (cmd == "ambient") {
          if(readvals(s, 3, values)) {
            ambient.r = values[0];
            ambient.g = values[1];
            ambient.b = values[2];
          }
        } else if (cmd == "emission") {
          if(readvals(s, 3, values)) {
            emission.r = values[0];
            emission.g = values[1];
            emission.b = values[2];
          }
        } else if (cmd == "diffuse"){
          if(readvals(s, 3, values)) {
            diffuse.r = values[0];
            diffuse.g = values[1];
            diffuse.b = values[2];
          }
        } else if (cmd == "specular") {
          if(readvals(s, 3, values)) {
            specular.r = values[0];
            specular.g = values[1];
            specular.b = values[2];
          }
        } else if (cmd == "shininess") {
          if(readvals(s, 1, values)) {
            shininess = values[0];
          }
        } else if (cmd =="point") {

          if(readvals(s, 6, values)) {
            Light * pl = new Light(values[0], values[1], values[2], 1.0,
              values[3], values[4], values[5]);
            pl->attenuation_terms = attenuation;
            lights.push_back(pl);
          }

        } else if (cmd == "directional") {

          if(readvals(s, 6, values)) {
            Light * dl = new Light(values[0], values[1], values[2], 0.0,
              values[3], values[4], values[5]);

            // This makes it so that there is NO attenuation
            dl->attenuation_terms = vec3(1, 0, 0);
            lights.push_back(dl);
          }

        } else if (cmd == "translate") {
          validinput = readvals(s, 3, values);
          if(validinput) {
            mat4 translate = Transforms::translate(values[0], values[1], values[2]);
            rightmultiply(translate, transfstack);
          }
        } else if (cmd == "rotate") {
          validinput = readvals(s, 4, values);
          if(validinput) {
            mat3 rotate = Transforms::rotate(vec3(values[0], values[1], values[2]), values[3]);
            rightmultiply(mat4(rotate), transfstack);\
          }
        } else if (cmd == "scale") {
          validinput = readvals(s, 3, values);
          if(validinput) {
            mat4 scale = Transforms::scale(values[0], values[1], values[2]);
            rightmultiply(scale, transfstack);
          }
        } else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top());
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n";
          } else {
            transfstack.pop();
          }
        }
        else {
          cerr << "Not processing " << cmd << "; skipping for now" << endl;
        }
      }
      getline(in, str);
    }

    cout << "Finished reading in scene file. Beginning ray tracing..." << endl;

  } else {
    cerr << "Unable to Open Input Data File " << filename << "\n";
    throw 2;
  }
}
