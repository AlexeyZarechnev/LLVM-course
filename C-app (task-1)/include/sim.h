#ifndef SIM
#define SIM

#define PIXEL_SCALE 3

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 900

#ifdef __cplusplus
    #define EXTERN extern "C"
#else
    #define EXTERN
#endif

EXTERN int init(void);

EXTERN void fill_init_state(int state[WINDOW_WIDTH / PIXEL_SCALE + 2][WINDOW_HEIGHT / PIXEL_SCALE + 2]);

EXTERN void put_pixel(int x, int y, int rgb);

EXTERN int flush(void);

EXTERN void quit(void);

EXTERN void app(void);

#endif