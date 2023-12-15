#include <iostream>
#include <fstream>
#include <limits>

#include "painter.h"
#include "util.h"
#include "scene.h"

const Color BACKGROUND_COLOR = (Color){0, 0, 0};

void Painter::outputImage() {
    fetchImage();

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

void Painter::setScene(Scene scene) {
    scene_ = scene;
}

void Painter::fetchImage() {
    pixel_colors.clear();
    Coord3d origin = {0, 0, 0};
    for (int x = -canvas_.width/2; x <= canvas_.width/2; x++) {
        for (int y = -canvas_.height/2; y <= canvas_.height/2; y++) {
            Coord3d pixel_viewport_pos = canvasToViewport((Coord2d){(float)x, (float)y});
            pixel_colors.push_back(traceRay(origin, pixel_viewport_pos, 0, std::numeric_limits<float>::max()));
        }
    }
    return;
}

Color Painter::traceRay(
    Coord3d origin, Coord3d pixel_viewport_pos, float t_min, float t_max) {
    float closest_t = std::numeric_limits<float>::max();
    Sphere* closest_sphere = nullptr;
    for (Sphere sphere : scene_.spheres) {
        std::pair<float, float> intersections = intersectRaySphere(origin, pixel_viewport_pos, sphere);
        if (t_min < intersections.first &&
            intersections.first < t_max &&
            intersections.first < closest_t) {
            closest_sphere = &sphere;
            closest_t = intersections.first;
        }
        if (t_min < intersections.second &&
            intersections.second < t_max &&
            intersections.second < closest_t) {
            closest_sphere = &sphere;
            closest_t = intersections.second;
        }
    }
    if (closest_sphere == nullptr) {
        return BACKGROUND_COLOR;
    }
    return closest_sphere->color;
}

std::pair<float, float> Painter::intersectRaySphere(
    Coord3d origin, Coord3d pixel_viewport_pos, Sphere sphere) {
    std::pair<float, float> intersections;
    intersections.first = 1.0;
    intersections.second = 2.0;
    return intersections;
}

Coord3d Painter::canvasToViewport(Coord2d pixel_position) {
    return (Coord3d){
        (pixel_position.x/canvas_.width) * viewport_.width,
        (pixel_position.y/canvas_.height) * viewport_.height,
        viewport_.d};
}
