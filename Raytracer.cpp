#include "Raytracer.h"
#include <vector>
#include <cfloat>
#include <iostream>
#include <cmath>

void  Raytracer::trace(Ray * ray, int depth, glm::vec3 * retlight) {

  float thit;
  float smallest_thit = FLT_MAX;
  Intersection closest_in;
  Intersection in;

  std::vector<Shape*>::iterator it = shapes.begin();
  std::vector<Shape*>::iterator end = shapes.end();
  Shape * closestObject = 0;
  Shape * currentObject;

  bool hit = false;
  for(; it != end; it++) {
    if (!depth) {
      (*retlight) = vec3(0, 0, 0);
      return;
    }

    hit = (*it)->intersect(ray, &thit, &in);
    if(hit && thit < smallest_thit && thit >= 0) {
      smallest_thit = thit;
      closestObject = *it;
      closest_in = in;
    }

  }

  glm::vec3 finallight = vec3(0, 0, 0);
  if(closestObject) {
    finallight = compute_light(&closest_in, closestObject, ray, depth);
  }

  (*retlight) = vec3(finallight);

}

glm::vec3 Raytracer::compute_light(Intersection * in, Shape * closestObject, Ray * ray, int depth) {

  std::vector<Light*>::iterator lit = lights.begin();
  std::vector<Light*>::iterator end = lights.end();
  glm::vec3 finalcolor = closestObject->getFragColor();

  for(; lit != end; lit++) {
    Light * working = *lit;
    vec3 position, light_direction;

    if(working->props.w == 1) { // Must be a point light
      position = vec3(working->props);
      light_direction = normalize(position - in->pos);
    } else if(working->props.w == 0) { // Must be a directional light
      light_direction = normalize(vec3(working->props));
    } else {
      std::cout << "Invalid light properties; not a point or directional light" << std::endl;
    }

    // Compute if in shadow or not
    std::vector<Shape*>::iterator it = shapes.begin();
    std::vector<Shape*>::iterator end = shapes.end();

    bool hit = false;
    Ray shadow_ray;
    shadow_ray.pos = in->pos + (float)0.0001 * light_direction;
    shadow_ray.dir = light_direction;

    float thit;
    Intersection dummy;

    for(; it != end; it++) {
      hit = (*it)->intersect(&shadow_ray, &thit, &dummy);
      if(hit) break;
    }
    if(hit) {
      // Compute reflectiveness using recursive ray tracing. If the specular is
      // 0, this acts as the visibility component.
      // Ray reflect_ray;
      // reflect_ray.dir = -ray->dir - (2.0f * in->normal * dot(-ray->dir, in->normal));
      // reflect_ray.pos = in->pos;
      // vec3 retlight = vec3(0, 0, 0);
      // trace(&reflect_ray, depth -1, &retlight);
      // finalcolor += retlight;
      continue;
    }

    // Vector between light direction and eyevector, which is the ray direction
    vec3 halfvector = normalize(light_direction + (-ray->dir));

    // Take into account attenuation. Direction lights will only have first attenuation
    // term applied
    float distance = glm::length(position - ray->pos); // TODO: This might not be right?
    vec3 lightcolor = working->color /
      (float)(
        working->attenuation_terms.x +
        (working->attenuation_terms.y * distance) +
        (working->attenuation_terms.z * std::pow(distance, 2))
      );

    float nDotL = dot(in->normal, light_direction);
    vec3 lambert = closestObject->diffuse * lightcolor * std::max(nDotL, (float)0.0);

    float nDotH = dot(in->normal, halfvector);
    vec3 phong = closestObject->specular * lightcolor * std::pow(std::max(nDotH, (float)0.0), closestObject->shininess);

    // float reflective_recursion =

    finalcolor += (lambert + phong);
  }

  // Clamping
  if (finalcolor.r > 1) finalcolor.r = 1.0;
  if (finalcolor.g > 1) finalcolor.g = 1.0;
  if (finalcolor.b > 1) finalcolor.b = 1.0;

  return finalcolor;

}
