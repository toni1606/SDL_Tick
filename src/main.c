// CLI Implementation of Tick Tack Toe
#ifdef CLI_APP
#include "../headers/cli.h"
int main(void) {
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);

  unsigned int turn = 0;
  while (true) {
    turn++;
    printf("Turn %d\n", turn);

    int tick_res = cli_tick(&board);
    if (tick_res == X) {
      printf("You won!!!\n");
      break;
    } else if (tick_res == O) {
      printf("CPU won!!!\n");
      break;
    } else if (tick_res == 5) {
      printf("Draw!!!\n");
      break;
    }
  }

  game_board_free(&board);
  return 0;
}
#else
// GUI (sort of) Implementation of Tick Tack Toe
#include "../headers/gui.h"
int main(void) {
  gui_t gui;
  game_board_t board;

  game_board_new(&board, 9, 3, O, X);

  gui_start(&gui, board, "Tick Tack Toe", 512, 512);

  while (true) {
    int res = gui_tick(&gui);
    if (res == X) {
      printf("You won!!!\n");
      break;
    } else if (res == O) {
      printf("CPU won!!!\n");
      break;
    } else if (res == 5) {
      printf("Draw!!!\n");
      break;
    }
  }

  gui_end(&gui);
  return 0;
}
#endif
