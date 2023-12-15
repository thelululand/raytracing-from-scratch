#include <iostream>
#include <fstream>

#include "painter.h"

void Painter::OutputImage() {
    std::ofstream f(file_name_, std::ofstream::trunc);
    f << "P3\n";
    f << image_height_ << " " << image_width_ << "\n";
    f << "255\n";
    for (int i = 0; i < image_height_; i++) {
        f << "\n";
        for (int j = 0; j < image_width_; j++) {
            PixelColor p = pixel_colors.at(i * image_height_ + j);
            f << p.r  << " " << p.g << " " << p.b << " ";
        }
    }
    f.close();
    return;
}

