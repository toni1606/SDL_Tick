#include "../headers/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

typedef struct {
  SDL_Window *window;
} gui_t;

int gui_start(gui_t *gui, char *title, unsigned int width, unsigned int height);
void gui_end(gui_t *g);
