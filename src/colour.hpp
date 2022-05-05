/* 
 * Colours, colour palettes for the terminal, and more.
 *
 * Made by DagothBob (https://github.com/DagothBob) 
 */

#include <array>
#include "types.hpp"

#ifndef TERM3D_COLOUR_H
#define TERM3D_COLOUR_H

namespace Colour {
    /* Colour to be used per-pixel in the renderer screen buffer. */
    class Pixel_Colour {
        private:

        V3D rgb;

        public:

        /* Safe constructor for pixel colours. Use this one if you can, so
        colour values are bound between 0 and 255. */
        Pixel_Colour(uint8_t r, uint8_t g, uint8_t b);

        /* Pixel colours use RGB with values between 0-255. This is hard to 
        enforce using the linear algebra backend (Eigen) which is used to
        store the values, so make sure you don't pass values higher than 255 
        (or negative values), because bad things will happen with NCURSES. 
        This won't happen with the separated RGB constructor. */
        Pixel_Colour(V3D rgb);

        void set_rgb(uint8_t r, uint8_t g, uint8_t b);

        /* Get red value. */
        uint8_t r();

        /* Get green value. */
        uint8_t g();

        /* Get blue value. */
        uint8_t b();

        /* You shouldn't need this function unless you are performing
        linear algebraic operations on the values of the rgb value. */
        V3D get_rgb();
    };

    /* NCURSES has 7 colours that can be redefined (COLOR_BLACK cannot be
    redefined). Colours can only be redefined once, so your chosen palette
    must be used for the duration of the whole program. */
    class Colour_Palette {
        public:

        /* Default NCURSES terminal colours */
        static std::array<Pixel_Colour, 7> const Terminal_Colours;

        std::array<Pixel_Colour, 7> palette;

        /* Creates a palette that is a copy of the default NCURSES colours. */
        Colour_Palette();

        
        Colour_Palette(std::array<Pixel_Colour, 7> _palette);
    };

    typedef short palette_colour;

    /* Convert RGB colour value (0-255) to value used by NCURSES for
    colour definitions (0-1000). */
    inline short RGB_TO_TERM_COL(double x) {
        return static_cast<short>(static_cast<int>((x / 256) * 1000));
    }

    /* For a given RGB colour -- finds the colour in the given palette
    with the shortest euclidean distance and returns its index. */
    palette_colour rgb_to_palette_colour(Pixel_Colour rgb, Colour_Palette palette);

    /* Averages (finds the midpoint between) the two colours c1 and c2. */
    Pixel_Colour average_colour(Pixel_Colour c1, Pixel_Colour c2);
}

#endif
