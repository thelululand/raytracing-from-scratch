#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <optional>

#include "painter.h"
#include "util.h"
#include "scene.h"

namespace {

// a dot b
float dot(Vec3 a, Vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// a - b
Vec3 subtract(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

} // namespace


const Color BACKGROUND_COLOR = (Color){0, 0, 0};

void Painter::OutputImage() {
    FetchImage();
    if (canvas_.height * canvas_.width != pixel_colors.size()) {
        std::cout << "\ncanvas pixels: "
                << canvas_.height * canvas_.width 
                << ". Got " << pixel_colors.size();
        throw std::invalid_argument("canvas pixel size don't equal pixel colors size.");
    }

    std::ofstream f(file_name_, std::ofstream::trunc);
    f << "P3\n";
    f << canvas_.width << " " << canvas_.height << "\n";
    f << "255\n";
    for (int i = 0; i < canvas_.height; i++) {
        f << "\n";
        for (int j = 0; j < canvas_.width; j++) {
            Color p = pixel_colors.at(i * canvas_.height + j);
            f << p.r  << " " << p.g << " " << p.b << " ";
        }
    }
    f.close();
    return;
}

void Painter::SetScene(Scene scene) {
    scene_ = scene;
}

void Painter::SetOrigin(Vec3 origin) {
    origin_ = origin;
}

void Painter::FetchImage() {
    pixel_colors.clear();
    // We need to start from positive height because PPM image file starts with upper left.
    for (int y = canvas_.height/2; y > -canvas_.height/2; y--) {
        for (int x = -canvas_.width/2; x < canvas_.width/2; x++) {
            Vec3 pixel_viewport_pos = CanvasToViewport((Vec2){(float)x, (float)y});
            pixel_colors.push_back(TraceRay(origin_, pixel_viewport_pos, 1, std::numeric_limits<float>::max()));
        }
    }
    return;
}

void Painter::DebugTraceRay(Vec3 pixel_viewport_pos) {
    Color color = TraceRay(origin_, pixel_viewport_pos, 1, std::numeric_limits<float>::max());
    std::cout << "\nCOLOR: " << color.r << " " << color.g << " " << color.b;
}

Color Painter::TraceRay(
    Vec3 origin, Vec3 pixel_viewport_pos, float t_min, float t_max) {
    float closest_t = std::numeric_limits<float>::max();
    std::optional<Sphere> closest_sphere;
    for (Sphere sphere : scene_.spheres) {
        std::pair<float, float> intersections = IntersectRaySphere(origin, pixel_viewport_pos, sphere);
        if (t_min < intersections.first &&
            intersections.first < t_max &&
            intersections.first < closest_t) {
            closest_sphere = sphere;
            closest_t = intersections.first;
        }
        if (t_min < intersections.second &&
            intersections.second < t_max &&
            intersections.second < closest_t) {
            closest_sphere = sphere;
            closest_t = intersections.second;
        }
    }
    if (!closest_sphere.has_value()) {
        return BACKGROUND_COLOR;
    }
    return closest_sphere->color;
}


std::pair<float, float> Painter::IntersectRaySphere(
    Vec3 origin, Vec3 pixel_viewport_pos, Sphere sphere) {
    std::pair<float, float> intersections;

    float r = sphere.radius;
    Vec3 center_to_origin = subtract(origin, sphere.center);

    float a = dot(pixel_viewport_pos, pixel_viewport_pos);
    float b = 2 * dot(center_to_origin, pixel_viewport_pos);
    float c = dot(center_to_origin, center_to_origin) - (r * r);

    float discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        intersections.first = std::numeric_limits<float>::max();
        intersections.second = std::numeric_limits<float>::max();
        return intersections;
    }

    intersections.first = (-b + sqrt(discriminant)) / (2 * a);
    intersections.second = (-b - sqrt(discriminant)) / (2 * a);
    return intersections;
}

Vec3 Painter::CanvasToViewport(Vec2 pixel_position) {
    return (Vec3){
        (pixel_position.x/canvas_.width) * viewport_.width,
        (pixel_position.y/canvas_.height) * viewport_.height,
        viewport_.d};
}
