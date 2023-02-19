#include "../headers/gui.h"

int gui_start(char *title, unsigned int width, unsigned int height) {
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not start video subsystem\n");
    return -1;
  }

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (!window) {
    fprintf(stderr, "Could not create window\n");
    return -2;
  }

  SDL_Delay(5000);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
