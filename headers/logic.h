#include <stdbool.h>
#include <stdlib.h>

#define UNIMPLEMENTED(...)                                                     \
  do {                                                                         \
    printf("%s:%d: UNIMPLEMENTED: %s \n", __FILE__, __LINE__, __VA_ARGS__);    \
    exit(1);                                                                   \
  } while (0);

typedef enum { N = 0, X = 1, O = 2 } game_state_t;

typedef struct {
  game_state_t *values;
  unsigned int row_len;
  unsigned int len;
  bool is_cpu_turn;
} game_board_t;

char game_state_tc(game_state_t s);

int game_board_new(game_board_t *board, unsigned int len, unsigned int row_len);
void game_board_print(game_board_t *board);
int game_board_turn(game_board_t *board, game_state_t val, unsigned int row,
                    unsigned int col);
int game_board_check_winner(game_board_t *board);
