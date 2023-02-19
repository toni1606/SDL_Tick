#include "../headers/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

typedef struct {
  SDL_Window *window;
  SDL_Rect *cols;
  SDL_Rect *rows;
} gui_t;

int gui_start(gui_t *gui, char *title, unsigned int width, unsigned int height);
void gui_end(gui_t *g);

void gui_render_playground(gui_t *gui);
