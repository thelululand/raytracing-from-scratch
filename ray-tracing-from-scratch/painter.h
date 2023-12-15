#include <iostream>

#include "canvas.h"

class Painter {
    public:
        Painter(int image_width, int image_height, std::string file_name) {
            image_width_ = image_width;
            image_height_ = image_height;
            file_name_ = file_name;
            for (int i = 0; i < image_height; i++) {
                for (int j = 0; j < image_width; j++) {
                    pixel_colors.push_back((Color){255, 0, 255});
                }
            }
        };

        void OutputImage();

    private:
        int image_width_;
        int image_height_;
        std::string file_name_;
        std::vector<Color> pixel_colors;
};