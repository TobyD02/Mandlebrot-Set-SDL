# Mandlebrot Set generator in C++
## Description
This program generates the mandelbrot set and exports it as a .bmp file. This was created using C++ and SDL2.
## How to use
Firstly compile the program using CMAKE. Then simply run the program and it should generate a file named "Mandlebrot.bmp" in the same directory as the file. A resolution scale modifier can be added on the commandline, e.g:

    - ./build/project 1000

Will construct the image at a scale of 1000 (default is 100).
