#include "Scene.h"

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

  Sampler sampler(800, 600);
  Sample sample;
  RGBQUAD color;
  Film film;
  Ray ray;
  Raytracer raytracer;

  //TODO: Remove after milestone
  Point v0(-1, -1, 0);
  Point v1(1, -1, 0);
  Point v2(1, 1, 0);
  Point v3(-1, 1, 0);
  Triangle triangle(v0, v1, v2);
  addShape(&triangle);

  Camera camera(glm::vec3(-4, -4, 4),
                glm::vec3(1, 0, 0),
                glm::vec3(0, 1, 0),
                30.0);

  while (sampler.getSample(&sample)) {
    camera.generateRay(sample, &ray);
    raytracer.trace(ray, 5, &color);
    film.commit(sample, color);
  }

  film.writeImage();
}
