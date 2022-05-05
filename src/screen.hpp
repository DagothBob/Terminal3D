/* 
 * Terminal screen.
 *
 * Made by DagothBob (https://github.com/DagothBob) 
 */

#include "colour.hpp"

#ifndef TERM3D_SCREEN_H
#define TERM3D_SCREEN_H

namespace Screen {
    /* A character represents a 1Wx2H pixel block.
       Both pixels being populated is represented by an '8' character.
       Just the top pixel is a '*', just the bottom is '.', and none is a 
       space. */
    struct character_palette
    {
        char none;
        char upper;
        char lower;
        char both;
    };
    extern character_palette char_palette;
    
    extern size_t char_cols; // # terminal columns.
    extern size_t char_rows; // # terminal rows.
    extern bool terminal_colours; // Has terminal colour support.
    extern bool change_colours; // Terminal can redefine colours.
    extern Colour::Colour_Palette colour_palette; // Palette to colour the screen

    /* Initialise the screen with the default NCURSES colour palette. */
    bool init_screen();

    /* Initialise the screen with the given colour palette. */
    bool init_screen(Colour::Colour_Palette col_palette);

    /* Write the screen to the terminal and clear the renderer screen buffer. */
    void next_frame();

    /* Copy the renderer screen buffer to the terminal. */
    void draw_screen();

    /* Close the NCURSES terminal screen. */
    void close_screen();

    /* Find the average RGB colour between c1 and c2. */
    short avg_char_colour(Colour::Pixel_Colour c1, Colour::Pixel_Colour c2);
}
#endif
