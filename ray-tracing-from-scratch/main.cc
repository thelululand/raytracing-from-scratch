#include <iostream>

#include "canvas.h"
#include "painter.h"
#include "sphere.h"

int main() {
    std::cout << "\n=============STARTING!===========\n";

    int image_height = 720;
    int image_width = 1020;
    Painter painter = Painter(
        image_width, image_height, /*file_name=*/"image.ppm");
    painter.OutputImage();
    // Sphere sphere1 = Sphere(
    //     /*radius=*/1.0, (Coordinate){0, 0, 0}, (Color){255, 0, 0});
    std::cout << "\n=============ENDED!==============\n";
}