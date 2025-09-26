#ifndef SIM
#define SIM

#define PIXEL_SCALE 3

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 900

int init(void);

void fill_init_state(int state[WINDOW_WIDTH / PIXEL_SCALE + 2][WINDOW_HEIGHT / PIXEL_SCALE + 2]);

void put_pixel(int x, int y, int rgb);

int flush(void);

void quit(void);

void app(void);

#endif