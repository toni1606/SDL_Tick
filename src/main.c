#include "../headers/logic.h"
#include <stdio.h>

int main(void) {
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);

  board.values[2] = X;
  board.values[4] = X;
  board.values[6] = X;

  game_board_print(&board);

  printf("%d\n", game_board_check_winner(&board));

  game_board_free(&board);
  return 0;
}
