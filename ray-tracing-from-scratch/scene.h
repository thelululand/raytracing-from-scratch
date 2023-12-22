#include "util.h"

#ifndef  SCENE_H 
#define SCENE_H 

struct Sphere {
    double radius;
    Vec3 center;
    Color color;
    std::string name;
};

enum LightType { AMBIENT, DIRECTIONAL, POINT};

struct Light {
    LightType type;
    double intensity;
    Vec3 position;
};

struct Scene {
    std::vector<Sphere> spheres;
};

#endif