#include "Scene.h"

Scene::Scene() {}

void Scene::render() {

  Sampler sampler(100, 100);
  Sample sample;
  RGBQUAD color;
  Film film;
  Ray ray;
  Camera camera(glm::vec3(-4, -4, 4),
                glm::vec3(1, 0, 0),
                glm::vec3(0, 1, 0),
                30.0);

  while (!sampler.getSample(&sample)) {
    camera.generateRay(sample, &ray);
    //raytracer.trace(ray, &color);
    film.commit(sample, color);
  }

  film.writeImage();
}
