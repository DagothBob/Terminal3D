/* 
 * Made by DagothBob (https://github.com/DagothBob) 
 */

#include <ncurses.h>
#include <iostream>
#include "colour.hpp"
#include "render.hpp"
#include "screen.hpp"

using namespace Screen;

size_t Screen::char_cols;
size_t Screen::char_rows;
bool Screen::terminal_colours;
bool Screen::change_colours;
Colour::Colour_Palette Screen::colour_palette;

Screen::character_palette Screen::char_palette = {
    .none = ' ',
    .upper = '*',
    .lower = '.',
    .both = '8',
};

bool Screen::init_screen() {
    return init_screen(Colour::Colour_Palette::Terminal_Colours);
}

bool Screen::init_screen(Colour::Colour_Palette col_palette) {
    if (!initscr()) {
        std::cout << "Failed to initialise screen.\n";
        close_screen();

        return false;
    }

    if (has_colors()) {
        terminal_colours = true;
        std::cout << "Terminal has colour support.\n";

        colour_palette = col_palette;
        start_color();

        if (can_change_color()) {
            change_colours = true;
            std::cout << "Colour definitions can be changed.\n";
        }
        else {
            change_colours = false;
            std::cout << "Colour definitions cannot be changed.\n";
        }

        for (size_t i = 1; i < 8; i++) {
            if (change_colours) {
                if (init_color(static_cast<short>(i), 
                    Colour::RGB_TO_TERM_COL(colour_palette.palette[i-1].r()),
                    Colour::RGB_TO_TERM_COL(colour_palette.palette[i-1].g()),
                    Colour::RGB_TO_TERM_COL(colour_palette.palette[i-1].b())) == ERR) 
                {
                    std::cout << "Failed to initialise colour " << i << std::endl;
                }
            }

            init_pair(static_cast<short>(i), static_cast<short>(i), COLOR_BLACK);
        }
    }
    else {
        terminal_colours = false;
        change_colours = false;
        std::cout << "Terminal doesn't have colour support.\n";
    }

    size_t r, c; // Rows, columns
    getmaxyx(stdscr, r, c);

    char_cols = c;
    char_rows = r;

    Renderer::init_renderer(char_cols, char_rows);

    noecho(); // Don't echo user input to the terminal screen

    return true;
}

void Screen::next_frame() {
    draw_screen();
    Renderer::reset_screen();
}

void Screen::draw_screen() {
    char current_char = '|'; // If this ever gets displayed - something went wrong
    short char_colour;

    for (size_t i = 0; i < char_cols; i++) {
        for (size_t j = 0; j < char_rows; j++) {
            std::optional<Colour::Pixel_Colour> top = Renderer::screen_buffer[i][j*2];
            std::optional<Colour::Pixel_Colour> bottom = Renderer::screen_buffer[i][(j*2)+1];

            // Both pixels
            if (top && bottom) {
                current_char = char_palette.both;
                char_colour = Colour::rgb_to_palette_colour(Colour::average_colour(top.value(), bottom.value()), colour_palette);
            }
            // Only top pixel
            else if (top) {
                current_char = char_palette.upper;
                char_colour = Colour::rgb_to_palette_colour(top.value(), colour_palette);
            }
            // Only bottom pixel
            else if (bottom) {
                current_char = char_palette.lower;
                char_colour = Colour::rgb_to_palette_colour(bottom.value(), colour_palette);
            }
            // No pixels
            else {
                current_char = char_palette.none;
                char_colour = COLOR_BLACK;
            }

            if (terminal_colours) {
                attron(COLOR_PAIR(char_colour));
            }

            mvaddch(j, i, current_char);

            if (terminal_colours) {
                attroff(COLOR_PAIR(char_colour));
            }
        }
    }

    refresh();
}

void Screen::close_screen() {
    endwin();
}
