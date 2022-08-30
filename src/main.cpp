#include <SDL.h>
#include <cmath>
#include <complex>

// TODO:
// - Add arguments to commandline
//      - Max Iterations, Start and end values.
// - Rename scale variable to image scale. And add new scale variable that changes the zoom.
// - Add colour palletes

// Set max iterations for mandlebrot
const int MAX_ITER = 200;

// Set real values start and end points
const double R_START = -2;
const double R_END = 1;

// Set imaginary values start and end points
const double I_START = -1;
const double I_END = 1;

// Set dimensions
int SCALE;
int WIDTH = (R_END - R_START);
int HEIGHT = (I_END - I_START);

using namespace std;

// Returns how many iterations to exceed bounds
int Mandlebrot(complex<double> c) {

    complex<double> z(0, 0);
    int n = 0;
    while (abs(z) <= 2 && n < MAX_ITER) {
        z = pow(z, 2.0);
        z += c;
        n += 1;
    }

    return n;
}


void DrawMandlebrot(SDL_Surface* surface) {
    // Lock surface so pixels can be set
    SDL_LockSurface(surface);

    // Do mandelbrot stuff
    int offset;
    Uint32 colour;
    Uint8 r, g, b, p_colour;
    complex<double> c;
    int n;
    Uint32* buffer = (Uint32*) surface->pixels;

    int count = 0;
    int total = WIDTH * HEIGHT;

    for (double row = 0; row < HEIGHT; row++) {
        for (double col = 0; col < WIDTH; col++) {
            // Get pixel position in array
            offset = row * WIDTH + col;

            // Get relative position
            c = { R_START + (col / WIDTH) * (R_END - R_START), 
                I_START + (row / HEIGHT) * (I_END - I_START)};

            // Get mandlebrot iterations for that coordinate
            n = Mandlebrot(c);

            if (n == MAX_ITER) count++;

            // Set rgb values accordingly
            if (n != MAX_ITER) {
                p_colour = (((float)n / MAX_ITER) * 255);
            } else {
                p_colour = 0;
            }

            // Set pixel colour
            colour = SDL_MapRGB(surface->format, p_colour, p_colour, p_colour); // Sets pixel values according to position

            // Update pixels array
            buffer[offset] = colour;
        }
    }

    // Unlock surface
    SDL_UnlockSurface(surface);

    printf("%d/%d\n", count, total);
}

// Main function
// Takes command line argument specifing scale (Defaults to 100 if none is specified)
int main(int argc, char* argv[]) {

    // Set scale
    if (argc > 1) SCALE = strtol(argv[1], NULL, 10);
    else SCALE = 100;

    // Set dimensions
    WIDTH *= SCALE;
    HEIGHT *= SCALE;

    // Initialise SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Generate surface to draw to
    SDL_Surface* surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);

    // Generate and draw mandlebrot
    DrawMandlebrot(surface);

    // Save as image
    if (SDL_SaveBMP(surface, "Mandlebrot.bmp") != 0) 
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());


    // Free surface and quit
    SDL_FreeSurface(surface);
    SDL_Quit();
}