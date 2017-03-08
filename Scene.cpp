#include "Scene.h"

Scene::Scene() {}

void Scene::render() {

  Sampler sampler(100, 100);
  Sample sample;
  RGBQUAD color;
  Film film;

  while (!sampler.getSample(&sample)) {
    //camera.generateRay(sample, &ray);
    //raytracer.trace(ray, &color);
    film.commit(sample, color);
  }

  film.writeImage();
}
