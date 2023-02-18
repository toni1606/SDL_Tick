#include "../headers/logic.h"
#include <stdio.h>

int main(void) {
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);
  game_board_print(&board);

  board.values[0] = O;
  board.values[1] = O;
  board.values[2] = X;

  printf("%d\n", game_board_check_winner(&board));

  game_board_free(&board);
  return 0;
}
