#include "sim.h"

#define WIDTH (WINDOW_WIDTH / PIXEL_SCALE)
#define HEIGHT (WINDOW_HEIGHT / PIXEL_SCALE)

void app(void) {
  int cur_state[WIDTH + 2][HEIGHT + 2] = {};
  int next_state[WIDTH + 2][HEIGHT + 2] = {};

  fill_init_state(cur_state);

  for (;;) {
    for (int i = 1; i < WIDTH + 1; ++i) {
      for (int j = 1; j < HEIGHT + 1; ++j) {
        int sum = cur_state[i][j + 1] + cur_state[i][j - 1] +
                  cur_state[i + 1][j] + cur_state[i - 1][j] +
                  cur_state[i - 1][j - 1] + cur_state[i - 1][j + 1] +
                  cur_state[i + 1][j - 1] + cur_state[i + 1][j + 1];
        next_state[i][j] = ((sum == 3) || (cur_state[i][j] && sum == 2));
        put_pixel(i - 1, HEIGHT - j, next_state[i][j] ? 0xFFFFFF : 0x0);
      }
    }
    if (flush()) {
      return;
    }

    for (int i = 1; i < WIDTH + 1; ++i) {
      for (int j = 1; j < HEIGHT + 1; ++j) {
        int sum = next_state[i][j + 1] + next_state[i][j - 1] +
                  next_state[i + 1][j] + next_state[i - 1][j] +
                  next_state[i - 1][j - 1] + next_state[i - 1][j + 1] +
                  next_state[i + 1][j - 1] + next_state[i + 1][j + 1];
        cur_state[i][j] = ((sum == 3) || (next_state[i][j] && sum == 2));
        put_pixel(i - 1, HEIGHT - j, cur_state[i][j] ? 0xFFFFFF : 0x0);
      }
    }
    if (flush()) {
      return;
    }
  }
}