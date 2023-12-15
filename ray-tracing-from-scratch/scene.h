#include "util.h"

#ifndef  SCENE_H 
#define SCENE_H 

struct Sphere {
    float radius;
    Coord3d center;
    Color color;
};

struct Scene {
    std::vector<Sphere> spheres;
};

#endif