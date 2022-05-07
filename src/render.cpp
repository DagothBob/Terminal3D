/* 
 * Made by DagothBob (https://github.com/DagothBob) 
 */

#include "render.hpp"
#include "types.hpp"

using namespace Renderer;

size_t Renderer::screen_width;
size_t Renderer::screen_height;
std::vector<std::vector<std::optional<Colour::Pixel_Colour>>> Renderer::screen_buffer;

void Renderer::init_renderer(size_t width, size_t height) {
    screen_width = width;
    screen_height = height * 2;
    reset_screen();
}

void Renderer::reset_screen() {
    screen_buffer = std::vector<std::vector<std::optional<Colour::Pixel_Colour>>>(
        screen_width, 
        std::vector<std::optional<Colour::Pixel_Colour>>(
            screen_height, 
            std::optional<Colour::Pixel_Colour>()));
}

void Renderer::bounds_test() {
    Renderer::screen_buffer[coords_to_wt(-1)][coords_to_ht(0.0)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(-1)][coords_to_ht(1.0)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(0.0)][coords_to_ht(-1)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(0.0)][coords_to_ht(0.0)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(0.0)][coords_to_ht(1.0)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(1.0)][coords_to_ht(-1)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(1.0)][coords_to_ht(0.0)] = Colour::Pixel_Colour(255, 255, 255);
    Renderer::screen_buffer[coords_to_wt(1.0)][coords_to_ht(1.0)] = Colour::Pixel_Colour(255, 255, 255);
}

void Renderer::fill_screen() {
    for (size_t s = 0; s < Renderer::screen_height; s++) {
        for (size_t p = 0; p < Renderer::screen_width; p++) {
            Renderer::screen_buffer[p][s] = Colour::Pixel_Colour(255, 255, 255);
        }
    }
}

Ray::Ray(V3D _origin, V3D _direction):
origin(_origin),
direction(_direction),
colour() {}

V3D Ray::get_at(double t) {
    return origin + (t * direction);
}

Camera::Camera():
Camera(V3D(0, 0, 0), V3D(0, 0, -1), V3D(0, 1, 0), M_PI_2, static_cast<double>(Renderer::screen_width) / static_cast<double>(Renderer::screen_height)) {}

Camera::Camera(V3D lookfrom, V3D lookat, V3D vup, double fov_radians, double aspect_ratio) {
    double h = tan(fov_radians/2); // Distance between centre of screen and top
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    V3D w = (lookfrom - lookat).normalized(); // Points behind the camera
    V3D u = vup.cross(w).normalized(); // Points straight right
    V3D v = w.cross(u); // Points straight down

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    upper_left = origin - (horizontal/2) - (vertical/2) - w;
}

Ray Camera::get_ray(double s, double t) {
    return Ray(origin, upper_left + (s*horizontal) + (t*vertical) - origin);
}
