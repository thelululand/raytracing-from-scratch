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
    Scene scene;

    Sphere red_sphere;
    red_sphere.name = "red_sphere";
    red_sphere.radius = 1.0f;
    red_sphere.color = (Color){255, 0, 0}; // red
    red_sphere.center = vec3(0.0f, -1.0f, 3.0f);
    red_sphere.specular = 500; // Shiny
    scene.spheres.push_back(red_sphere);

    Sphere blue_sphere;
    blue_sphere.name = "blue_sphere";
    blue_sphere.radius = 1.0f;
    blue_sphere.color = (Color){0, 0, 255}; // blue
    blue_sphere.center = vec3(2.0f, 0.0f, 4.0f);
    blue_sphere.specular = 500; // Shiny
    scene.spheres.push_back(blue_sphere);

    Sphere green_sphere;
    green_sphere.name = "green_sphere";
    green_sphere.radius = 1.0f;
    green_sphere.color = (Color){0, 255, 0}; // green
    green_sphere.center = vec3(-2.0f, 0.0f, 4.0f);
    green_sphere.specular = 10; // Somewhat shiny
    scene.spheres.push_back(green_sphere);

    Sphere sphere4;
    sphere4.name = "sphere4";
    sphere4.radius = 5000.0f;
    sphere4.color = (Color){255, 255, 0}; // yellow
    sphere4.center = vec3(0.0f, -5001.0f, 0.0f);
    scene.spheres.push_back(sphere4);

    Light ambient_light;
    ambient_light.type = AMBIENT;
    ambient_light.intensity = 0.2;
    scene.lights.push_back(ambient_light);

    Light point_light;
    point_light.type = POINT;
    point_light.intensity = 0.6;
    point_light.position = vec3(2, 1, 0);
    scene.lights.push_back(point_light);

    Light directional_light;
    directional_light.type = DIRECTIONAL;
    directional_light.intensity = 0.2;
    directional_light.direction = vec3(1, 4, 4);
    scene.lights.push_back(directional_light);
    
    painter.SetScene(scene);

    painter.OutputImage();
    std::cout << "\n=============ENDED!==============\n";
}