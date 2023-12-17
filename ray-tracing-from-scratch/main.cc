#include <iostream>

#include "util.h"
#include "painter.h"

int main() {
    std::cout << "\n=============STARTING!===========\n";

    float image_height = 500.0f;
    float image_width = 500.0f;
    Painter painter = Painter(
        (Canvas){image_width, image_height},
        /*file_name=*/"image.ppm",
        (Viewport){1,1,1});

    Sphere sphere1;
    sphere1.name = "sphere1";
    sphere1.radius = 1.0f;
    sphere1.color = (Color){0, 0, 255}; // blue
    sphere1.center = (Vec3){2.0f, 0.0f, 4.0f};

    Sphere sphere2;
    sphere2.name = "sphere2";
    sphere2.radius = 1.0f;
    sphere2.color = (Color){0, 255, 0}; // green
    sphere2.center = (Vec3){-2.0f, 0.0f, 4.0f};

    Sphere sphere3;
    sphere3.name = "sphere3";
    sphere3.radius = 1.0f;
    sphere3.color = (Color){255, 0, 0}; // red
    sphere3.center = (Vec3){0.0f, -1.0f, 3.0f};

    Sphere sphere4;
    sphere4.name = "sphere4";
    sphere4.radius = 5000.0f;
    sphere4.color = (Color){255, 255, 0};
    sphere4.center = (Vec3){0.0f, -5001.0f, 0.0f};

    Scene scene;
    scene.spheres.push_back(sphere1);
    scene.spheres.push_back(sphere2);
    scene.spheres.push_back(sphere3);
    scene.spheres.push_back(sphere4);
    
    painter.SetScene(scene);

    painter.OutputImage();
    std::cout << "\n=============ENDED!==============\n";
}