#include "sim.h"

int main(void) {
  if (init()) {
    return 1;
  }

  app();
  quit();
}