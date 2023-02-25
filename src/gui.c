#include "../headers/gui.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
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
  col.x = CELL_SPACE + PADDING;
  col.y = PADDING;
  col.w = GIRTH;
  col.h = (board.len / board.row_len) * (CELL_SPACE + PADDING);

  row.x = PADDING;
  row.y = CELL_SPACE + PADDING;
  row.w = board.row_len * (CELL_SPACE + PADDING);
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
  SDL_Rect rect;
  rect.x = 0;
  rect.y = gui->base_col.y;
  rect.w = gui->base_col.w;
  rect.h = gui->base_col.h;

  for (int i = 0; i < gui->board.row_len - 1; i++) {

    rect.x += gui->base_col.x + GIRTH;

    if (SDL_RenderFillRect(gui->rendr, &rect) < 0) {
      fprintf(stderr, "Could not fill the column %d: %s\n", i, SDL_GetError());
      return -1;
    }
  }

  return 0;
}

static int gui_render_rows(gui_t *gui) {
  SDL_Rect rect;
  rect.x = gui->base_row.x;
  rect.y = 0;
  rect.w = gui->base_row.w;
  rect.h = gui->base_row.h;

  for (int i = 0; i < (gui->board.len / gui->board.row_len) - 1; i++) {
    rect.y += gui->base_row.y + GIRTH;

    if (SDL_RenderFillRect(gui->rendr, &rect) < 0) {
      fprintf(stderr, "Could not fill the row %d: %s\n", i, SDL_GetError());
      return -1;
    }
  }

  return 0;
}

// Source:
// https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
static void gui_render_circle(gui_t *gui, int center_x, int center_y, int r) {
  int diameter = r * 2;

  int x = r - 1;
  int y = 0;
  int tx = 1;
  int ty = 1;
  int err = tx - diameter;

  while (x >= y) {
    SDL_RenderDrawPoint(gui->rendr, center_x + x, center_y - y);
    SDL_RenderDrawPoint(gui->rendr, center_x + x, center_y + y);
    SDL_RenderDrawPoint(gui->rendr, center_x - x, center_y - y);
    SDL_RenderDrawPoint(gui->rendr, center_x - x, center_y + y);
    SDL_RenderDrawPoint(gui->rendr, center_x + y, center_y - x);
    SDL_RenderDrawPoint(gui->rendr, center_x + y, center_y + x);
    SDL_RenderDrawPoint(gui->rendr, center_x - y, center_y - x);
    SDL_RenderDrawPoint(gui->rendr, center_x - y, center_y + x);

    if (err <= 0) {
      y++;
      err += ty;
      ty += 2;
    }

    if (err > 0) {
      x--;
      tx += 2;
      err += tx - diameter;
    }
  }
}

static int gui_render_sq(gui_t *gui, int x, int y, int a) {
  int ha = a / 2;
  SDL_Rect rect = {.x = x - ha, .y = y - ha, .w = a, .h = a};

  if (SDL_RenderFillRect(gui->rendr, &rect) < 0) {
    fprintf(stderr, "Could not fill square: %s\n", SDL_GetError());
    return -1;
  }

  return 0;
}

static int gui_render_game_state(gui_t *gui) {
  int y = PADDING + CELL_SPACE / 2;
  for (int i = 0; i < gui->board.len / gui->board.row_len; i++) {
    int x = PADDING + CELL_SPACE / 2;
    for (int j = 0; j < gui->board.row_len; j++) {
      switch (gui->board.values[i * gui->board.row_len + j]) {
      case X:
        gui_render_sq(gui, x, y, (int)(CELL_SPACE * 0.8));
        break;
      case O:
        gui_render_circle(gui, x, y, (int)(CELL_SPACE * 0.4));
        break;
      case N:
        break;
      }

      // PADDING + 2 * (CELL_SPACE / 2) + GIRTH => PADDING + CELL_SPACE + GIRTH
      x += PADDING + CELL_SPACE + GIRTH;
    }

    // PADDING + 2 * (CELL_SPACE / 2) + GIRTH => PADDING + CELL_SPACE + GIRTH
    y += PADDING + CELL_SPACE + GIRTH;
  }

  return 0;
}

int gui_render_playground(gui_t *gui) {
  // Change Render Color to black to clear renderer.
  SDL_SetRenderDrawColor(gui->rendr, 0, 0, 0, 255);

  // Clear the rendering.
  SDL_RenderClear(gui->rendr);

  // Change Render Color.
  SDL_SetRenderDrawColor(gui->rendr, 255, 255, 255, 255);

  // Draw the coulmns.
  gui_render_cols(gui);

  // Draw the rows.
  gui_render_rows(gui);

  // Draw game board state.
  gui_render_game_state(gui);

  // Change Back buffer with front buffer.
  SDL_RenderPresent(gui->rendr);
  return 0;
}

int gui_tick(gui_t *gui) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    gui_render_playground(gui);

    switch (event.type) {
    case SDL_QUIT:
      return 2;
    case SDL_MOUSEBUTTONUP:
      switch (event.button.type) {
      case SDL_MOUSEBUTTONUP:
        if (event.button.x > gui->base_row.w || event.button.x < PADDING ||
            event.button.y > gui->base_col.h || event.button.y < PADDING) {
          break;
        }
        int col = event.button.x / gui->board.row_len;
        int row = event.button.y / (gui->board.len / gui->board.row_len);
        printf("col: %d, row: %d\n", col, row);
        break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        return 1;
      }
    }
  }
  return 0;
}
