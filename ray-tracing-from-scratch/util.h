#ifndef  UTIL_H 
#define UTIL_H 

struct Color {
    int r;
    int g;
    int b;
};

struct Coord3d {
    float x;
    float y;
    float z;
};

struct Coord2d {
    float x;
    float y;
};

struct Canvas {
    float width;
    float height;
};

struct Viewport {
    float width;
    float height;
    // z-coordidate of the viewport
    float d;
};
#endif