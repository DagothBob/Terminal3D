/*
 * Rendering system.
 * All 3D calculations are performed in a virtual coordinate space and
 * ray-traced to the screen buffer.
 * 
 * Made by DagothBob (https://github.com/DagothBob)
 */

#include <optional>
#include <vector>
#include "colour.hpp"
#include "types.hpp"

#ifndef RENDER_H
#define RENDER_H

namespace Renderer {
    extern size_t screen_width; // Calculated based on terminal character width.
    extern size_t screen_height; // Calculated based on terminal character height.
    extern std::vector<std::vector<std::optional<Colour::Pixel_Colour>>> screen_buffer;

    /* x <- {-1, 1} produces screen pixel for width. */
    inline size_t coords_to_wt(double x) { 
        return (screen_width-1) * static_cast<size_t>((x+1)/2);
    }

    /* x <- {-1, 1} produces screen pixel for height. */
    inline size_t coords_to_ht(double y) { 
        return (screen_height-1) * static_cast<size_t>((y+1)/2);
    }

    /* Initialise renderer system by setting screen dimensions based on 
    terminal dimensions, and setting up the screen buffer. */
    void init_renderer(size_t width, size_t height);

    /* Resets the screen buffer to all black pixels. */
    void reset_screen();

    /* Tests screen orientation and pixel bounds. */
    void bounds_test();

    /* Fill screen buffer for basic testing. */
    void fill_screen();

    /* Ray originating at the Camera. Intersects coordinate-space geometry
    and returns a pixel colour. */
    class Ray {
        public:

        V3D origin; // Originating point. Set by its parent Camera.
        V3D direction; // Unit vector pointing to a screen-space pixel.
        std::optional<Colour::Pixel_Colour> colour;

        Ray(V3D _origin, V3D _direction);

        /* Get ray's direction vector scaled by t. */
        V3D get_at(double t);
    };

    /* Camera exists in coordinate-space and consists of an origin point,
    two vectors pointing orthogonally in the x and y axis, and a vector
    pointing to the bottom-left of the virtual screen. */
    class Camera {
        public:

        V3D origin;
        V3D horizontal;
        V3D vertical;
        V3D lower_left;

        /* Set Camera with values appropriate for the test cases that come
        with this package. */
        Camera();

        /* lookfrom: Origin point for the camera
           lookat: Direction the camera is facing
           vup: Unit vector pointing in the direction that is "up"
           fov_radians: Vertical field-of-view in radians
           aspect ratio: How "wide" your screen width is compared to how "high" your screen height is */
        Camera(V3D lookfrom, V3D lookat, V3D vup, double fov_radians, double aspect_ratio);

        /* s: % current screen width to point ray at
           t: % current screen height to point ray at */
        Ray get_ray(double s, double t);
    };
}
#endif
