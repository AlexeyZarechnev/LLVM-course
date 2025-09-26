#include <SDL2/SDL.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

#include "sim.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"

#define FRAME_TICKS 60

static const int RGB_BLACK = 0x000000;

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static Uint32 Ticks = 0;

static int get_r(int rgb) {
    return (rgb >> 16) & 0xFF;
}

static int get_g(int rgb) {
    return (rgb >> 8) & 0xFF;
}

static int get_b(int rgb) {
    return rgb & 0xFF;
}

int init(void) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    if (!renderer || !window) {
        printf("Renderer creation error: %s\n", SDL_GetError());
        quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, get_r(RGB_BLACK), get_g(RGB_BLACK), get_b(RGB_BLACK), SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    put_pixel(0, 0, 0);
    flush();
    return 0;
}

void fill_init_state(int state[WINDOW_WIDTH / PIXEL_SCALE + 2][WINDOW_HEIGHT / PIXEL_SCALE + 2]) {
    // cycle 1
    state[51][151] = 1;
    state[52][151] = 1;
    state[51][152] = 1;
    state[52][152] = 1;

    // cycle2
    state[85][153] = 1;
    state[86][153] = 1;
    state[85][154] = 1;
    state[86][154] = 1;

    // left arrow
    state[64][154] = 1;
    state[63][154] = 1;
    state[62][153] = 1;
    state[61][152] = 1;
    state[61][151] = 1;
    state[61][150] = 1;
    state[62][149] = 1;
    state[63][148] = 1;
    state[64][148] = 1;
    state[65][151] = 1;
    
    state[66][153] = 1;
    state[67][152] = 1;
    state[67][151] = 1;
    state[67][150] = 1;
    state[66][149] = 1;
    state[68][151] = 1;

    // right arrow
    state[71][152] = 1;
    state[72][152] = 1;
    state[71][153] = 1;
    state[72][153] = 1;
    state[71][154] = 1;
    state[72][154] = 1;
    state[73][151] = 1;
    state[75][151] = 1;
    state[75][150] = 1;
    state[73][155] = 1;
    state[75][155] = 1;
    state[75][156] = 1;
}

void put_pixel(int x, int y, int rgb) {
    SDL_SetRenderDrawColor(renderer, get_r(rgb), get_g(rgb), get_b(rgb), SDL_ALPHA_OPAQUE);
    for (int x_d = 0; x_d < PIXEL_SCALE; ++x_d) {
        for (int y_d = 0; y_d < PIXEL_SCALE; ++y_d) {
            SDL_RenderDrawPoint(renderer, PIXEL_SCALE * x + x_d, PIXEL_SCALE * y + y_d);
        }
    }
    Ticks = SDL_GetTicks();
}

int flush(void) {
    SDL_PumpEvents();
    if (SDL_HasEvent(SDL_QUIT)) {
        return 1;
    }
    Uint32 cur_ticks = SDL_GetTicks() - Ticks;
    if (cur_ticks < FRAME_TICKS)
    {
        SDL_Delay(FRAME_TICKS - cur_ticks);
    }
    SDL_RenderPresent(renderer);
    return 0;
}

void quit(void) {
    if (window) {
        SDL_DestroyRenderer(renderer);
    }
    if (renderer) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}