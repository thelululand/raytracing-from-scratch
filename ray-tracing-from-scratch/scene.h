#include "util.h"
#include "vec3.h"

#ifndef  SCENE_H 
#define SCENE_H 

struct Sphere {
    double radius;
    vec3 center;
    Color color;
    double specular = -1;
    std::string name;
};

enum LightType { AMBIENT, DIRECTIONAL, POINT};

struct Light {
    LightType type;
    double intensity;
    vec3 position;
    vec3 direction;
};

struct Scene {
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
};

#endif