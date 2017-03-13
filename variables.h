#include "Scene.h"
#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>

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
