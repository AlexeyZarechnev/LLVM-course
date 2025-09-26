#include "sim.h"

void app(void) {
  const int width = WINDOW_WIDTH / PIXEL_SCALE;
  const int height = WINDOW_HEIGHT / PIXEL_SCALE;
  int cur_state[width + 2][height + 2] = {};
  int next_state[width + 2][height + 2] = {};

  fill_init_state(cur_state);

  for (;;) {
    for (int i = 1; i < width + 1; ++i) {
      for (int j = 1; j < height + 1; ++j) {
        int sum = cur_state[i][j + 1] + cur_state[i][j - 1] +
                  cur_state[i + 1][j] + cur_state[i - 1][j] +
                  cur_state[i - 1][j - 1] + cur_state[i - 1][j + 1] +
                  cur_state[i + 1][j - 1] + cur_state[i + 1][j + 1];
        next_state[i][j] = ((sum == 3) || (cur_state[i][j] && sum == 2));
        put_pixel(i - 1, height - j, next_state[i][j] ? 0xFFFFFF : 0x0);
      }
    }
    if (flush()) {
      return;
    }

    for (int i = 1; i < width + 1; ++i) {
      for (int j = 1; j < height + 1; ++j) {
        int sum = next_state[i][j + 1] + next_state[i][j - 1] +
                  next_state[i + 1][j] + next_state[i - 1][j] +
                  next_state[i - 1][j - 1] + next_state[i - 1][j + 1] +
                  next_state[i + 1][j - 1] + next_state[i + 1][j + 1];
        cur_state[i][j] = ((sum == 3) || (next_state[i][j] && sum == 2));
        put_pixel(i - 1, height - j, cur_state[i][j] ? 0xFFFFFF : 0x0);
      }
    }
    if (flush()) {
      return;
    }
  }
}