#include "../headers/cli.h"
#include <stdio.h>

int main(void) {
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);

  unsigned int turn = 0;
  while (true) {
    turn++;
    printf("Turn %d\n", turn);

    if (cli_tick(&board) == X) {
      printf("You won!!!");
      break;
    } else if (cli_tick(&board) == O) {
      printf("CPU won!!!");
      break;
    }
  }

  game_board_free(&board);
  return 0;
}
