#include "Scene.h"
#include "variables.h"
#include <iostream>

using namespace std;

void Scene::render() {

  Sampler sampler(width, height);
  Sample sample;
  RGBQUAD color;
  Film film;

  cout << fixed;
  cout.precision(2);

  while (sampler.getSample(&sample)) {
    camera.generateRay(sample, &ray);
    raytracer.trace(ray, 5, &color);
    film.commit(sample, color);
    cout << (sample.y / width * 100) << "% of Pixels Traced..." << "\r";
  }

  cout << "Done!" << endl;
  film.writeImage();
}
