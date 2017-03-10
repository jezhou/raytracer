#include "Scene.h"
#include "variables.h"

Scene::Scene() {
  shapes = new std::vector<Shape *>();
}

void Scene::addShape(Shape * shape) {
  shapes->push_back(shape);
}

std::vector<Shape *> * Scene::getShapes() {
  return shapes;
}

void Scene::render() {

  Sampler sampler(width, height);
  Sample sample;
  RGBQUAD color;
  Film film;
  Ray ray;
  Raytracer raytracer;

  Camera camera(glm::vec3(0,0, 4),
                glm::vec3(0, 0, 0),
                glm::vec3(0, 1, 0),
                30.0);

  while (sampler.getSample(&sample)) {
    camera.generateRay(sample, &ray);
    raytracer.trace(ray, 5, &color);
    film.commit(sample, color);
  }

  film.writeImage();
}
