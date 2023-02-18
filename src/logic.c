#include "../headers/logic.h"
#include <stdio.h>

char game_state_tc(game_state_t s) {
  char out = '\0';
  switch (s) {
  case N:
    out = 'N';
    break;
  case X:
    out = 'X';
    break;
  case O:
    out = 'O';
    break;
  }

  return out;
}

int game_board_new(game_board_t *board, unsigned int len,
                   unsigned int row_len) {
  board->values = calloc(len, sizeof(game_state_t));
  if (!board->values) {
    fprintf(stderr, "Could not allocate memory");
    return -1;
  }

  board->is_cpu_turn = false;
  board->row_len = row_len;
  board->len = len;

  return 0;
}

void game_board_print(game_board_t *board) {
  for (int i = 0; i < board->len; i += board->row_len) {
    for (int j = 0; j < board->row_len; j++)
      printf(" %c ", game_state_tc(board->values[i + j]));
    printf("\n");
  }
}

int game_board_turn(game_board_t *board, game_state_t val, unsigned int row,
                    unsigned int col) {
  UNIMPLEMENTED("game_board_turn");
}
int game_board_check_winner(game_board_t *board) {
  UNIMPLEMENTED("game_board_winner");
}
