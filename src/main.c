#include "../headers/gui.h"
#include <stdio.h>

int main(void) {
  gui_t gui;
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);
  gui_start(&gui, board, "Tick Tack Toe", 512, 512);

  printf("Rect {x: %d, y: %d, w: %d, h: %d}\n", gui.base_col.x, gui.base_col.y,
         gui.base_col.w, gui.base_col.h);
  printf("Rect {x: %d, y: %d, w: %d, h: %d}\n", gui.base_row.x, gui.base_row.y,
         gui.base_row.w, gui.base_row.h);
  gui_render_playground(&gui);

  gui_end(&gui);
  return 0;
}

// int cli_main(void) {
//   game_board_t board;
//
//   game_board_new(&board, 9, 3, O, X);
//
//   unsigned int turn = 0;
//   while (true) {
//     turn++;
//     printf("Turn %d\n", turn);
//
//     int tick_res = cli_tick(&board);
//     if (tick_res == X) {
//       printf("You won!!!");
//       break;
//     } else if (tick_res == O) {
//       printf("CPU won!!!");
//       break;
//     }
//   }
//
//   game_board_free(&board);
//   return 0;
// }
