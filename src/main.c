#include "../headers/gui.h"
#include <stdio.h>

int main(void) {
  gui_t gui;
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);

  board.values[0] = X;
  board.values[1] = O;

  gui_start(&gui, board, "Tick Tack Toe", 512, 512);

  while (gui_tick(&gui) <= 0) {
  }

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
