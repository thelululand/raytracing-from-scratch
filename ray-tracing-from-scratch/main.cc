#include <iostream>

#include "painter.h"

int main() {
    std::cout << "\n=============STARTING!===========\n";

    int image_width = 1020;
    int image_height = 720;
    Painter painter = Painter(image_width, image_height, "image.ppm");
    painter.OutputImage();
    std::cout << "\n=============ENDED!==============\n";
}