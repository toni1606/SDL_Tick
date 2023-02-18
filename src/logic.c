#include "../headers/logic.h"
#include <stdio.h>
#include <stdlib.h>

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

int game_board_new(game_board_t *board, unsigned int len, unsigned int row_len,
                   game_state_t cpu_tok, game_state_t plr_tok) {
  if (!board) {
    fprintf(stderr, "Board pointer was NULL");
    return -1;
  }

  board->values = calloc(len, sizeof(game_state_t));
  if (!board->values) {
    fprintf(stderr, "Could not allocate memory");
    return -1;
  }

  board->is_cpu_turn = false;
  board->row_len = row_len;
  board->len = len;
  board->cpu_tok = cpu_tok;
  board->plr_tok = plr_tok;

  return 0;
}

int game_board_free(game_board_t *board) {
  if (!board) {
    fprintf(stderr, "Board pointer was NULL");
    return -1;
  }

  free(board->values);
  return 0;
}

void game_board_print(game_board_t *board) {
  for (int i = 0; i < board->len; i += board->row_len) {
    for (int j = 0; j < board->row_len; j++)
      printf(" %c ", game_state_tc(board->values[i + j]));
    printf("\n");
  }
}

int game_board_turn(game_board_t *board, unsigned int row, unsigned int col) {
  if (!board) {
    fprintf(stderr, "Board pointer was NULL");
    return -1;
  } else if (row >= (board->len / board->row_len)) {
    fprintf(stderr, "Invalid row value");
    return -2;
  } else if (col >= board->row_len) {
    fprintf(stderr, "Invalid column value");
    return -3;
  }

  if (board->is_cpu_turn)
    board->values[(row * board->row_len) + col] = board->cpu_tok;
  else
    board->values[(row * board->row_len) + col] = board->plr_tok;

  board->is_cpu_turn = !board->is_cpu_turn;

  return 0;
}
int game_board_check_winner(game_board_t *board) {
  UNIMPLEMENTED("game_board_winner");
}
