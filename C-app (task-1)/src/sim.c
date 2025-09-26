#include <SDL2/SDL.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "sim.h"

#define FRAME_TICKS 60

static const int RGB_BLACK = 0x000000;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint32 Ticks = 0;

static int get_r(int rgb) { return (rgb >> 16) & 0xFF; }

static int get_g(int rgb) { return (rgb >> 8) & 0xFF; }

static int get_b(int rgb) { return rgb & 0xFF; }

int init(void) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    printf("SDL initialization error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
                              &renderer);

  if (!renderer || !window) {
    printf("Renderer creation error: %s\n", SDL_GetError());
    quit();
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, get_r(RGB_BLACK), get_g(RGB_BLACK),
                         get_b(RGB_BLACK), SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  put_pixel(0, 0, 0);
  flush();
  return 0;
}

void fill_init_state(int state[WINDOW_WIDTH / PIXEL_SCALE + 2]
                              [WINDOW_HEIGHT / PIXEL_SCALE + 2]) {
  // cycle 1
  state[51][251] = 1;
  state[52][251] = 1;
  state[51][252] = 1;
  state[52][252] = 1;

  // cycle2
  state[85][253] = 1;
  state[86][253] = 1;
  state[85][254] = 1;
  state[86][254] = 1;

  // left arrow
  state[64][254] = 1;
  state[63][254] = 1;
  state[62][253] = 1;
  state[61][252] = 1;
  state[61][251] = 1;
  state[61][250] = 1;
  state[62][249] = 1;
  state[63][248] = 1;
  state[64][248] = 1;
  state[65][251] = 1;

  state[66][253] = 1;
  state[67][252] = 1;
  state[67][251] = 1;
  state[67][250] = 1;
  state[66][249] = 1;
  state[68][251] = 1;

  // right arrow
  state[71][252] = 1;
  state[72][252] = 1;
  state[71][253] = 1;
  state[72][253] = 1;
  state[71][254] = 1;
  state[72][254] = 1;
  state[73][251] = 1;
  state[75][251] = 1;
  state[75][250] = 1;
  state[73][255] = 1;
  state[75][255] = 1;
  state[75][256] = 1;
}

void put_pixel(int x, int y, int rgb) {
  SDL_SetRenderDrawColor(renderer, get_r(rgb), get_g(rgb), get_b(rgb),
                         SDL_ALPHA_OPAQUE);
  for (int x_d = 0; x_d < PIXEL_SCALE; ++x_d) {
    for (int y_d = 0; y_d < PIXEL_SCALE; ++y_d) {
      SDL_RenderDrawPoint(renderer, PIXEL_SCALE * x + x_d,
                          PIXEL_SCALE * y + y_d);
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
  if (cur_ticks < FRAME_TICKS) {
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