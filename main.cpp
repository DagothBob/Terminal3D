/* 
 * This is an example for drawing a sphere.
 * 
 * Made by DagothBob (https://github.com/DagothBob)
 */

#include <ncurses.h>
#include "include/Terminal3D"
#include "sphere.hpp"

void test(int choice);
void geometry_test(double _x, double _z);
void draw_schvantz(double _x, double _z);

int main(void) {
    if (!Screen::init_screen()) return EXIT_FAILURE;

    test(1);

    Screen::close_screen();

    return EXIT_SUCCESS;
}

void test(int choice) {
    switch (choice) {
        case 1:
        while (true) {
            for (double x = 0; x <= 2; x += 0.02) {
                geometry_test(x, 1);
                Screen::next_frame();
            }

            for (double z = 1; z >= -1; z -= 0.02) {
                geometry_test(2, z);
                Screen::next_frame();
            }

            for (double x = 2; x >= 0; x -= 0.02) {
                geometry_test(x, -1);
                Screen::next_frame();
            }

            for (double z = -1; z <= 1; z += 0.02) {
                geometry_test(0, z);
                Screen::next_frame();
            }
        }

        case 2:
        geometry_test(1, 1);
        Screen::next_frame();
        getch();
        break;

        default:
        while (true) {
            for (double x = 0; x <= 2; x += 0.01) {
                draw_schvantz(x, 1);
                Screen::next_frame();
            }

            for (double z = 1; z >= -1; z -= 0.01) {
                draw_schvantz(2, z);
                Screen::next_frame();
            }

            for (double x = 2; x >= 0; x -= 0.01) {
                draw_schvantz(x, -1);
                Screen::next_frame();
            }

            for (double z = -1; z <= 1; z += 0.01) {
                draw_schvantz(0, z);
                Screen::next_frame();
            }
        }
    }
}

/* Create a sphere around (0, 0, 0) and initialise the camera at
 (_x, 0, _z), pointing at the sphere. */
void geometry_test(double _x, double _z) {
    Renderer::Camera camera = Renderer::Camera(V3D(-1+_x, 0, -1+_z), V3D(0, 0, -1), V3D(0, 1, 0), M_PI_2, static_cast<double>(Renderer::screen_width) / static_cast<double>(Renderer::screen_height));
    Drawables::Draw_List objects;
    objects.add(std::make_shared<Sphere>(Sphere(V3D(0, 0, -1), 0.6)));

    for (size_t y = 0; y < Renderer::screen_height; y++) {
        for (size_t x = 0; x < Renderer::screen_width; x++) {
            double s = static_cast<double>(x) / static_cast<double>(Renderer::screen_width-1);
            double t = static_cast<double>(y) / static_cast<double>(Renderer::screen_height-1);
            Drawables::Drawable::hit_record record;
            Renderer::Ray ray = camera.get_ray(s, t);

            if (objects.hit(ray, 0, static_cast<double>(INFINITY), record)) {
                Renderer::screen_buffer[x][y] = ray.colour;
            }
            else {
                Renderer::screen_buffer[x][y];
            }
        }
    }
}

/* Similar to geometry_test in many ways. */
void draw_schvantz(double _x, double _z) {
    Renderer::Camera camera = Renderer::Camera(V3D(-1+_x,  0, -1+_z), V3D(0, 0, -1), V3D(0, 1, 0), M_PI_2, static_cast<double>(Renderer::screen_width) / static_cast<double>(Renderer::screen_height));
    double offset = .3;
    Drawables::Draw_List oy_vey;
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(-0.2, 0+offset, -1), 0.3)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0.2, 0+offset, -1), 0.3)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.1+offset, -1), 0.2)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.2+offset, -1), 0.2)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.3+offset, -1), 0.2)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.4+offset, -1), 0.2)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.5+offset, -1), 0.2)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.6+offset, -1), 0.2)));
    oy_vey.add(std::make_shared<Sphere>(Sphere(V3D(0, -0.7+offset, -1), 0.2)));

    for (size_t y = 0; y < Renderer::screen_height; y++) {
        for (size_t x = 0; x < Renderer::screen_width; x++) {
            double s = static_cast<double>(x) / static_cast<double>(Renderer::screen_width-1);
            double t = static_cast<double>(y) / static_cast<double>(Renderer::screen_height-1);
            Drawables::Drawable::hit_record record;
            Renderer::Ray ray = camera.get_ray(s, t);

            if (oy_vey.hit(ray, 0, static_cast<double>(INFINITY), record)) {
                Renderer::screen_buffer[x][y] = ray.colour;
            }
            else {
                Renderer::screen_buffer[x][y];
            }
        }
    }
}
