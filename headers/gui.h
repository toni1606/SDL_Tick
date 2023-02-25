#include "../headers/logic.h"
#include "../headers/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <time.h>

#define CELL_SPACE 100
#define GIRTH 10
#define PADDING 20

typedef struct {
  SDL_Window *window;
  SDL_Renderer *rendr;
  SDL_Rect base_col;
  SDL_Rect base_row;
  game_board_t board;
} gui_t;

int gui_start(gui_t *gui, game_board_t board, char *title, unsigned int width,
              unsigned int height);
void gui_end(gui_t *g);

int gui_render_playground(gui_t *gui);

int gui_tick(gui_t *gui);
