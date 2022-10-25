#include <stdbool.h>
#include <stdio.h>

#include "lib/dames.h"

int main() {
  pion board[WIDTH_TABLE][HEIGHT_TABLE];
  init_table(board);
  print_board(board);
  pos piece1;
  piece1.x = 1;
  piece1.y = 0;
  pos dest;
  dest.x = 6;
  dest.y = 6;

  selection_pion(board, piece1, PLAYER_WHITE);
  return 0;
}
