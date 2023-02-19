#include "../headers/gui.h"
#include <SDL2/SDL_rect.h>

int gui_start(gui_t *gui, game_board_t board, char *title, unsigned int width,
              unsigned int height) {
  if (!gui) {
    fprintf(stderr, "gui_t supplied was NULL\n");
    return -3;
  }

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

  // 20 == padding
  SDL_Rect col = {0};
  col.x = CELL_SPACE + 20;
  col.y = 20;
  col.w = GIRTH;
  col.h = (board.len / board.row_len) * (GIRTH + CELL_SPACE + 20);

  SDL_Rect row = {0};
  row.x = 20;
  row.y = CELL_SPACE + 20;
  row.w = board.row_len * (GIRTH + CELL_SPACE + 20);
  col.h = GIRTH;

  gui->window = window;
  gui->board = board;
  gui->base_col = col;
  gui->base_row = row;

  return 0;
}

void gui_end(gui_t *g) {
  if (!g) {
    fprintf(stderr, "gui_t supplied was NULL\n");
    return;
  }

  SDL_DestroyWindow(g->window);
  SDL_Quit();

  game_board_free(&(g->board));
}
