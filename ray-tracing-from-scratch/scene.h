#include "util.h"

#ifndef  SCENE_H 
#define SCENE_H 

struct Sphere {
    float radius;
    Vec3 center;
    Color color;
    std::string name;
};

struct Scene {
    std::vector<Sphere> spheres;
};

#endif