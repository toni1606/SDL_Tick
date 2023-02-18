#include "../headers/logic.h"
#include <stdio.h>

int main(void) {
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);
  game_board_print(&board);
  for (int i = 0; i < board.len / board.row_len; i++) {
    for (int j = 0; j < board.row_len; j++) {
      game_board_turn(&board, i, j);
      game_board_print(&board);
      printf("\n");
    }
  }

  game_board_free(&board);
  return 0;
}
