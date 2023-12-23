#include <iostream>
#include <optional>

#include "util.h"
#include "scene.h"
#include "vec3.h"

class Painter {
    public:
        Painter(
            Canvas canvas, std::string file_name, Viewport viewport):
            canvas_(canvas), file_name_(file_name), viewport_(viewport) {
            SetOrigin(vec3(0, 0, 0));
        };

        // Outputs a ppm image file from `pixel_colors`.
        void OutputImage();
        
        // Sets a scene to paint.
        void SetScene(Scene scene);

        // Prints out a color value of TraceRay.
        void DebugTraceRay(vec3 pixel_viewport_pos);

        // Sets the origin of the camera.
        void SetOrigin(vec3 origin);

    private:
        // Trace every ray to the viewport and populates `pixel_colors`.
        void FetchImage();
        
        // Returns a color of the ray tracing result.
        Color TraceRay(vec3 origin, vec3 viewport_position, double t_min, double t_max, int recursion_depth = 3);

        // Returns a sphere and closest_t if the ray intersects with spheres. 
        std::pair<std::optional<Sphere>, double> ClosestIntersection(
            vec3 origin, vec3 pixel_viewport_pos, double t_min, double t_max);

        // Returns an intersection between the ray and the sphere.
        std::pair<double, double> IntersectRaySphere(vec3 origin, vec3 pixel_viewport_pos, Sphere sphere);
        
        // Converts the x, y coordidate in the canvas to the viewport coordidate.
        vec3 CanvasToViewport(Vec2 coord2d);

        // Returns the intensity of light at `point`, given a surface `normal`.
        double ComputeLighting(vec3 point, vec3 normal, vec3 inverse_ray, double specular);

        Canvas canvas_;
        Viewport viewport_;
        std::string file_name_;
        std::vector<Color> pixel_colors;
        Scene scene_;
        vec3 origin_;
};