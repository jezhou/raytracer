#include "Scene.h"
#include "Shape.h"
#include "Light.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <FreeImage.h>

#ifdef MAINPROGRAM
#undef EXTERN
#define EXTERN
#else
#undef EXTERN
#define EXTERN extern
#endif

class Scene;
class Film;
class Raytracer;

EXTERN int width;
EXTERN int height;
EXTERN int bits_per_pixel;

EXTERN Camera camera;
EXTERN Ray ray;
EXTERN Raytracer raytracer;
EXTERN const char * outputfilename;

EXTERN std::vector<glm::vec3> vertices;
EXTERN std::vector<Shape*> shapes;

EXTERN Scene scene;

EXTERN glm::vec3 ambient;
EXTERN glm::vec3 emission;
EXTERN glm::vec3 diffuse;
EXTERN glm::vec3 specular;
EXTERN glm::vec3 attenuation;
EXTERN float shininess;
EXTERN std::vector<Light*> lights;
