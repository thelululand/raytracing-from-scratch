#ifndef  UTIL_H 
#define UTIL_H 

struct Color {
    int r;
    int g;
    int b;
};

struct Vec3 {
    float x;
    float y;
    float z;
};

struct Vec2 {
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