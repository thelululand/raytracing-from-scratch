#include <iostream>

#include "util.h"
#include "scene.h"

class Painter {
    public:
        Painter(
            Canvas canvas, std::string file_name, Viewport viewport):
            canvas_(canvas), file_name_(file_name), viewport_(viewport) {
            SetOrigin((Vec3){0,0,0});
        };

        // Outputs a ppm image file from `pixel_colors`.
        void OutputImage();
        
        // Sets a scene to paint.
        void SetScene(Scene scene);

        // Prints out a color value of TraceRay.
        void DebugTraceRay(Vec3 pixel_viewport_pos);

        // Sets the origin of the camera.
        void SetOrigin(Vec3 origin);

    private:
        // Trace every ray to the viewport and populates `pixel_colors`.
        void FetchImage();
        
        // Returns a color of the ray tracing result.
        Color TraceRay(Vec3 origin, Vec3 viewport_position, float t_min, float t_max);

        // Returns an intersection between the ray and the sphere.
        std::pair<float, float> IntersectRaySphere(Vec3 origin, Vec3 pixel_viewport_pos, Sphere sphere);
        
        // Converts the x, y coordidate in the canvas to the viewport coordidate.
        Vec3 CanvasToViewport(Vec2 coord2d);

        Canvas canvas_;
        Viewport viewport_;
        std::string file_name_;
        std::vector<Color> pixel_colors;
        Scene scene_;
        Vec3 origin_;
};