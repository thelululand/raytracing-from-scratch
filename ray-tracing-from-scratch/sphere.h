#include "canvas.h"

class Sphere {
    public:
        Sphere(float radius, Coordinate center, Color color):
            radius_(radius), center_(center), color_(color) {
        };

    private:
        float radius_;
        Coordinate center_;
        Color color_;
};