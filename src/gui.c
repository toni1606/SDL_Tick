#include "../headers/gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

int gui_start() {
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not start video subsystem\n");
    return -1;
  }

  window =
      SDL_CreateWindow("Hello, World", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_RESIZABLE);

  if (!window) {
    fprintf(stderr, "Could not create window\n");
    return -2;
  }

  SDL_Delay(5000);

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
