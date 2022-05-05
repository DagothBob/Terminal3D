# Terminal 3D

Terminal3D is a 3D ray-tracing engine that uses your terminal emulator as the output screen. 

![Sphere rendered in a terminal emulator](https://i.imgur.com/uiZpHM4.png)

## Requirements
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [NCURSES](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/)

## Building

`cd Terminal3D`<br>
`./make`

You'll have to change the Makefile if you use a toolchain other than clang.

## Using the library
1. Include "./include/Terminal3D".
2. Call `Screen::init_screen()` to initialise the screen and renderer.
3. Extend `Drawables::Drawable` to create a geometry that has a ray-intersection equation. "sphere.hpp/cpp" is an example you can use.
4. Call your function(s) which write the screen buffer (geometry_test in the example).
5. Call `Screen::next_frame()` to have the screen buffer copied to the terminal window.
6. Call `Screen::close_screen()` when exiting, to free resources used by NCURSES.

## Attribution
Ray-tracing information from [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
