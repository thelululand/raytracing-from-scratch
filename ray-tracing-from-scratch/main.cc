#include <iostream>

#include "util.h"
#include "painter.h"

int main() {
    std::cout << "\n=============STARTING!===========\n";

    int image_height = 720;
    int image_width = 1020;
    Painter painter = Painter(
        (Canvas){image_width, image_height},
        /*file_name=*/"image.ppm",
        (Viewport){1,1,1});

    Sphere sphere1;
    sphere1.radius = 3;
    sphere1.color = (Color){0, 0, 255}; // blue
    sphere1.center = (Coord3d){2, 2, 2};

    Scene scene;
    scene.spheres.push_back(sphere1);
    
    painter.setScene(scene);

    painter.outputImage();
    std::cout << "\n=============ENDED!==============\n";
}