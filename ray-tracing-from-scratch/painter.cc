#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <optional>

#include "painter.h"
#include "util.h"
#include "scene.h"
#include "vec3.h"

namespace {

Color mul(Color color, double i) {
    return (Color){(int) (color.r * i), (int) (color.g * i), (int) (color.b * i)};
}

Color mul(double i, Color color) {
    return mul(color, i);
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

void Painter::SetOrigin(vec3 origin) {
    origin_ = origin;
}

void Painter::FetchImage() {
    pixel_colors.clear();
    // We need to start from positive height because PPM image file starts with upper left.
    for (int y = canvas_.height/2; y > -canvas_.height/2; y--) {
        for (int x = -canvas_.width/2; x < canvas_.width/2; x++) {
            vec3 pixel_viewport_pos = CanvasToViewport((Vec2){(double)x, (double)y});
            pixel_colors.push_back(TraceRay(origin_, pixel_viewport_pos, 1, std::numeric_limits<double>::max()));
        }
    }
    return;
}

void Painter::DebugTraceRay(vec3 pixel_viewport_pos) {
    Color color = TraceRay(origin_, pixel_viewport_pos, 1, std::numeric_limits<double>::max());
    std::cout << "\nCOLOR: " << color.r << " " << color.g << " " << color.b;
}

Color Painter::TraceRay(
    vec3 origin, vec3 pixel_viewport_pos, double t_min, double t_max) {
    double closest_t = std::numeric_limits<double>::max();
    std::optional<Sphere> closest_sphere;
    for (Sphere sphere : scene_.spheres) {
        std::pair<double, double> intersections = IntersectRaySphere(origin, pixel_viewport_pos, sphere);
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
    vec3 direction = pixel_viewport_pos - origin;
    vec3 point = origin + closest_t *  direction; // intersection
    vec3 normal = point - closest_sphere->center; 
    normal = normal / normal.length();
    return mul(closest_sphere->color, ComputeLighting(point, normal));
}


std::pair<double, double> Painter::IntersectRaySphere(
    vec3 origin, vec3 pixel_viewport_pos, Sphere sphere) {
    std::pair<double, double> intersections;

    double r = sphere.radius;
    vec3 center_to_origin = origin - sphere.center;

    double a = dot(pixel_viewport_pos, pixel_viewport_pos);
    double b = 2 * dot(center_to_origin, pixel_viewport_pos);
    double c = dot(center_to_origin, center_to_origin) - (r * r);

    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0) {
        intersections.first = std::numeric_limits<double>::max();
        intersections.second = std::numeric_limits<double>::max();
        return intersections;
    }

    intersections.first = (-b + sqrt(discriminant)) / (2 * a);
    intersections.second = (-b - sqrt(discriminant)) / (2 * a);
    return intersections;
}

vec3 Painter::CanvasToViewport(Vec2 pixel_position) {
    return (vec3){
        (pixel_position.x/canvas_.width) * viewport_.width,
        (pixel_position.y/canvas_.height) * viewport_.height,
        viewport_.d};
}

double Painter::ComputeLighting(vec3 point, vec3 normal) {
    double intensity = 0;
    for (Light light : scene_.lights) {
        if (light.type == AMBIENT) {
            intensity += light.intensity;
        } else {
            vec3 direction;
            if (light.type == POINT) {
                direction = light.position -point;
            } else {
                direction = light.direction;
            }
            double normal_dot_direction = dot(normal, direction);
            if (normal_dot_direction > 0) {
                intensity += (light.intensity * normal_dot_direction/(normal.length() * direction.length()));
            }
        }
    }
    return intensity;
}