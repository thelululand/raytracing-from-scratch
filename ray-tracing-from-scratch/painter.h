#include <iostream>

#include "util.h"
#include "scene.h"

class Painter {
    public:
        Painter(
            Canvas canvas, std::string file_name, Viewport viewport) {
            canvas_ = canvas;
            file_name_ = file_name;
            viewport_ = viewport;
            for (int i = 0; i < canvas_.height; i++) {
                for (int j = 0; j < canvas_.width; j++) {
                    pixel_colors.push_back((Color){255, 0, 255});
                }
            }
        };

        // Outputs a ppm image file from `pixel_colors`.
        void outputImage();
        
        // Sets a scene to paint.
        void setScene(Scene scene);

    private:
        // 
        void fetchImage();
        
        //
        Color traceRay(Coord3d origin, Coord3d viewport_position, float t_min, float t_max);
        
        // 
        std::pair<float, float> intersectRaySphere(Coord3d origin, Coord3d pixel_viewport_pos, Sphere sphere);
        
        // Converts the x, y coordidate in the canvas to the viewport coordidate.
        Coord3d canvasToViewport(Coord2d coord2d);

        Canvas canvas_;
        Viewport viewport_;
        std::string file_name_;
        std::vector<Color> pixel_colors;
        Scene scene_;
};