#include "../headers/gui.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

int gui_start(gui_t *gui, game_board_t board, char *title, unsigned int width,
              unsigned int height) {
  if (!gui) {
    fprintf(stderr, "gui_t supplied was NULL\n");
    return -3;
  }

  SDL_Window *window = NULL;
  SDL_Renderer *rendr = NULL;
  SDL_Rect col = {0};
  SDL_Rect row = {0};

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

  rendr = SDL_CreateRenderer(window, -1, 0);

  if (!rendr) {
    fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
    return -3;
  }

  // 20 == padding
  col.x = CELL_SPACE + 20;
  col.y = 20;
  col.w = GIRTH;
  col.h = (board.len / board.row_len) * (GIRTH + CELL_SPACE + 20);

  row.x = 20;
  row.y = CELL_SPACE + 20;
  row.w = board.row_len * (GIRTH + CELL_SPACE + 20);
  row.h = GIRTH;

  gui->window = window;
  gui->rendr = rendr;
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
  SDL_DestroyRenderer(g->rendr);
  SDL_Quit();

  game_board_free(&(g->board));
}

static int gui_render_cols(gui_t *gui) {
  for (int i = 0; i < gui->board.row_len - 1; i++) {
    SDL_Rect rect;

    rect.x = (CELL_SPACE + 20) * (i + 1);
    rect.y = gui->base_col.y;
    rect.w = gui->base_col.w;
    rect.h = gui->base_col.h;

    if (SDL_RenderFillRect(gui->rendr, &rect) < 0) {
      fprintf(stderr, "Could not fill the column %d: %s\n", i, SDL_GetError());
      return -1;
    }
  }

  return 0;
}

int gui_render_playground(gui_t *gui) {
  // Clear the rendering.
  SDL_RenderClear(gui->rendr);

  // Change Render Color.
  SDL_SetRenderDrawColor(gui->rendr, 255, 255, 255, 255);

  // Draw the rectangles.
  gui_render_cols(gui);

  // Draw the base row column.
  if (SDL_RenderFillRect(gui->rendr, &gui->base_row) < 0) {
    fprintf(stderr, "Could not fill row: %s\n", SDL_GetError());
    return -2;
  }

  // Change Back buffer with front buffer.
  SDL_RenderPresent(gui->rendr);
  SDL_Delay(5000);

  return 0;
}
