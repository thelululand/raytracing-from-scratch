#include <iostream>

#include "util.h"
#include "painter.h"
#include "vec3.h"

int main() {
    std::cout << "\n=============STARTING!===========\n";

    double image_height = 500.0f;
    double image_width = 500.0f;
    Painter painter = Painter(
        (Canvas){image_width, image_height},
        /*file_name=*/"image.ppm",
        (Viewport){1,1,1});

    Sphere sphere1;
    sphere1.name = "sphere1";
    sphere1.radius = 1.0f;
    sphere1.color = (Color){0, 0, 255}; // blue
    sphere1.center = vec3(2.0f, 0.0f, 4.0f);

    Sphere sphere2;
    sphere2.name = "sphere2";
    sphere2.radius = 1.0f;
    sphere2.color = (Color){0, 255, 0}; // green
    sphere2.center = vec3(-2.0f, 0.0f, 4.0f);

    Sphere sphere3;
    sphere3.name = "sphere3";
    sphere3.radius = 1.0f;
    sphere3.color = (Color){255, 0, 0}; // red
    sphere3.center = vec3(0.0f, -1.0f, 3.0f);

    Sphere sphere4;
    sphere4.name = "sphere4";
    sphere4.radius = 5000.0f;
    sphere4.color = (Color){255, 255, 0}; // yellow
    sphere4.center = vec3(0.0f, -5001.0f, 0.0f);

    Scene scene;
    scene.spheres.push_back(sphere1);
    scene.spheres.push_back(sphere2);
    scene.spheres.push_back(sphere3);
    scene.spheres.push_back(sphere4);

    Light light1;
    light1.type = AMBIENT;
    light1.intensity = 0.2;
    scene.lights.push_back(light1);

    Light light2;
    light2.type = POINT;
    light2.intensity = 0.6;
    light2.position = vec3(2, 1, 0);
    scene.lights.push_back(light2);

    Light light3;
    light3.type = DIRECTIONAL;
    light3.intensity = 0.2;
    light3.direction = vec3(1, 4, 4);
    scene.lights.push_back(light3);
    
    painter.SetScene(scene);

    painter.OutputImage();
    std::cout << "\n=============ENDED!==============\n";
}