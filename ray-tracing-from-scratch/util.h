#ifndef  UTIL_H 
#define UTIL_H 

struct Color {
    int r;
    int g;
    int b;
};

struct Vec3 {
    double x;
    double y;
    double z;
};

struct Vec2 {
    double x;
    double y;
};

struct Canvas {
    double width;
    double height;
};

struct Viewport {
    double width;
    double height;
    // z-coordidate of the viewport
    double d;
};
#endif