#include "../headers/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cli_tick(game_board_t *board) {
  game_board_print(board);

  // Check for the turn and react accordingly
  if (board->is_cpu_turn) {
    // Set random seed to time.
    srand(time(NULL));

    // Generate row and column and perform turn.
    // (rand() + MIN_VALUE) % MAX_VALUE
    // Repeat until valid numbers from generator.
    int col, row;
    do {
      col = rand() % board->row_len;
      row = rand() % (board->len / board->row_len);
    } while (game_board_turn(board, row, col) == -4);
  } else {
    unsigned int row, col;

    do {
      printf("Enter cell withh format = (row, col): ");
      scanf(" (%u, %u)", &row, &col);
    } while (game_board_turn(board, row, col) != 0);
  }

  return game_board_check_winner(board);
}
