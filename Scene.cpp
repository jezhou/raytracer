#include "Scene.h"
#include "variables.h"
#include <iostream>

using namespace std;

void Scene::render() {

  Sampler sampler(width, height);
  Sample sample;
  RGBQUAD color;
  Film film;
  glm::vec3 retlight;

  cout << fixed;
  cout.precision(2);

  while (sampler.getSample(&sample)) {
    camera.generateRay(sample, &ray);
    raytracer.trace(&ray, 5, &retlight);

    color.rgbGreen = 255 * retlight.g;
    color.rgbRed = 255 * retlight.b;
    color.rgbBlue = 255 * retlight.r;

    film.commit(sample, color);
    cout << (sample.y / height * 100) << "% of Pixels Traced..." << "\r";
    cout.flush();
  }

  //Purely for aesthetic reasons
  cout << "100% of Pixels Traced! Proceeding to write image..." << endl;

  film.writeImage();
}
