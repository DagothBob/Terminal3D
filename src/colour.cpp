/* 
 * Made by DagothBob (https://github.com/DagothBob)
 */

#include "colour.hpp"
#include "types.hpp"

using namespace Colour;

std::array<Pixel_Colour, 7> const Colour::Colour_Palette::Terminal_Colours = {{
    Pixel_Colour(255, 0, 0),    // COLOR_RED
    Pixel_Colour(0, 255, 0),    // COLOR_GREEN
    Pixel_Colour(255, 255, 0),  // COLOR_YELLOW
    Pixel_Colour(0, 0, 255),    // COLOR_BLUE
    Pixel_Colour(255, 0, 255),  // COLOR_MAGENTA
    Pixel_Colour(0, 255, 255),  // COLOR_CYAN
    Pixel_Colour(255, 255, 255) // COLOR_WHITE
}};

palette_colour Colour::rgb_to_palette_colour(Pixel_Colour rgb, Colour_Palette palette) {
    std::pair<palette_colour, Pixel_Colour> pal_col(0, palette.palette[0]);
    
    for (size_t i = 1; i < 7; i++) {
        Pixel_Colour current_palette = palette.palette[i];

        if (sqrt(pow(static_cast<double>(rgb.r()) - static_cast<double>(current_palette.r()), 2) + 
                 pow(static_cast<double>(rgb.g()) - static_cast<double>(current_palette.g()), 2) +
                 pow(static_cast<double>(rgb.b()) - static_cast<double>(current_palette.b()), 2)) <
            sqrt(pow(static_cast<double>(rgb.r()) - static_cast<double>(pal_col.second.r()), 2) +
                 pow(static_cast<double>(rgb.g()) - static_cast<double>(pal_col.second.g()), 2) +
                 pow(static_cast<double>(rgb.b()) - static_cast<double>(pal_col.second.b()), 2))) 
        {
            pal_col = std::pair(i, current_palette);    
        }
    }

    return pal_col.first;
}

Pixel_Colour Colour::average_colour(Pixel_Colour c1, Pixel_Colour c2) {
    return V3D((static_cast<double>(c1.r()) + static_cast<double>(c2.r())) / 2,
               (static_cast<double>(c1.g()) + static_cast<double>(c2.g())) / 2,
               (static_cast<double>(c1.b()) + static_cast<double>(c2.b())) / 2);
}

Colour_Palette::Colour_Palette():
palette(Terminal_Colours) {}

Colour_Palette::Colour_Palette(std::array<Pixel_Colour, 7> _palette):
palette(_palette) {}

Pixel_Colour::Pixel_Colour(uint8_t r, uint8_t g, uint8_t b):
rgb(V3D(r, g, b)) {}

Pixel_Colour::Pixel_Colour(V3D _rgb):
rgb(_rgb) {}

void Pixel_Colour::set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    rgb = V3D(r, g, b);
}

uint8_t Pixel_Colour::r() {
    return static_cast<uint8_t>(rgb[0]);
}

uint8_t Pixel_Colour::g() {
    return static_cast<uint8_t>(rgb[1]);
}

uint8_t Pixel_Colour::b() {
    return static_cast<uint8_t>(rgb[2]);
}

V3D Pixel_Colour::get_rgb() {
    return rgb;
}
