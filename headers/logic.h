#include "../headers/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { N = 0, X = 1, O = 2 } game_state_t;

typedef struct {
  game_state_t *values;

  game_state_t cpu_tok;
  game_state_t plr_tok;

  unsigned int row_len;
  unsigned int len;
  bool is_cpu_turn;
} game_board_t;

char game_state_tc(game_state_t s);

int game_board_new(game_board_t *board, unsigned int len, unsigned int row_len,
                   game_state_t cpu_tok, game_state_t plr_tok);
int game_board_free(game_board_t *board);

void game_board_print(game_board_t *board);
int game_board_turn(game_board_t *board, unsigned int row, unsigned int col);
int game_board_check_winner(game_board_t *board);
bool game_board_is_full(game_board_t *board);
