#include "../headers/logic.h"
#include <stdio.h>

int main(void) {
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);
  game_board_print(&board);

  board.values[2] = X;
  board.values[5] = X;
  board.values[8] = X;

  printf("%d\n", game_board_check_winner(&board));

  game_board_free(&board);
  return 0;
}
