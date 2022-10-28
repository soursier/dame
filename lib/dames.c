#include "dames.h"

#include <stdio.h>

void game() {
  pion board[WIDTH_TABLE][HEIGHT_TABLE];

  init_table(board);
  while (true) {
    print_board(board);
    player_turn(board, PLAYER_WHITE);
    print_board(board);
    player_turn(board, PLAYER_BLACK);
  }
}
void init_table(pion grille[][WIDTH_TABLE]) {
  for (int y = 0; y < HEIGHT_TABLE; y++) {
    for (int x = 0; x < WIDTH_TABLE; x++) {
      if (((x + y) % 2) && (y < 4)) {
        grille[y][x] = PION_WHITE;
      } else if (((x + y) % 2) && (y > HEIGHT_TABLE - 5)) {
        grille[y][x] = PION_BLACK;
      } else {
        grille[y][x] = PION_EMPTY;
      }
    }
  }
}

void print_board(pion grille[][WIDTH_TABLE]) {
  printf("   ");
  for (int i = 0; i < WIDTH_TABLE; i++) {
    printf("|%d|", i);
  }
  printf("\n");
  for (int y = 0; y < HEIGHT_TABLE; y++) {
    printf("|%d|", y);
    for (int x = 0; x < WIDTH_TABLE; x++) {
      printf("|");
      if (grille[y][x] == PION_BLACK) {
        printf("B");
      } else if (grille[y][x] == PION_WHITE) {
        printf("W");
      } else {
        printf(" ");
      }
      printf("|");
    }
    printf("\n");
  }
}
void print_moves(pion grille[][WIDTH_TABLE], player current_player);
void print_combos(pion grille[][WIDTH_TABLE], player current_player);

void ask_joueur_move(pion grille[][WIDTH_TABLE], move* his_move,
                     move possible_moves[], int nb_moves) {
  printf("%d coups sont possibles\n", nb_moves);
  for (int i = 0; i < nb_moves; i++) {
    printf("x = %d y = %d peut aller en x = %d y = %d\n",
           possible_moves[i].piece.x, possible_moves[i].piece.y,
           possible_moves[i].destination.x, possible_moves[i].destination.y);
  }
  selection_pion(grille, &(his_move->piece), possible_moves, nb_moves);
  selection_move(grille, his_move->piece, &(his_move->destination),
                 possible_moves, nb_moves);
}

void selection_pion(pion grille[][WIDTH_TABLE], pos* piece,
                    move possible_moves[], int nb_moves) {
  bool is_valid = false;
  int x = 0;
  int y = 0;
  while (!is_valid) {
    printf(
        "Veuillez selectionner les coordonnees de la piece a bouger ! x y\n");

    scanf("%d %d", &x, &y);

    for (int moves_index = 0; moves_index < nb_moves; moves_index++) {
      *piece = possible_moves[moves_index].piece;
      if ((piece->y == y) && (piece->x == x)) {
        is_valid = true;
      }
    }
  }
}

void selection_move(pion grille[][WIDTH_TABLE], pos piece, pos* dest,
                    move possible_moves[], int nb_moves) {
  bool is_valid = false;
  int x = 0;
  int y = 0;
  pos temp_piece;
  while (!is_valid) {
    printf("Veuillez selectionner les coordonnees de la destination ! x y\n");
    scanf("%d %d", &x, &y);
    for (int moves_index = 0; moves_index < nb_moves; moves_index++) {
      *dest = possible_moves[moves_index].destination;
      temp_piece = possible_moves[moves_index].piece;
      printf("la piece x = %d y = %d peut elle aller en x=%d y=%d ?\n", piece.x,
             piece.y, x, y);
      printf("celle ci x = %d y = %d peut aller en x = %d y = %d\n",
             temp_piece.x, temp_piece.y, dest->x, dest->y);
      if (((dest->y == y) && (dest->x == x)) &&
          ((temp_piece.y == piece.y) && (temp_piece.x == temp_piece.x))) {
        is_valid = true;
      }
    }
  }
}
bool is_his_piece(pion grille[][WIDTH_TABLE], player current_player,
                  pos piece) {
  if (grille[piece.y][piece.x] == PION_EMPTY) {
    return false;
  }
  if ((current_player == PLAYER_BLACK) &&
      (grille[piece.y][piece.x] == PION_BLACK)) {
    return true;
  }
  if ((current_player == PLAYER_WHITE) &&
      (grille[piece.y][piece.x] == PION_WHITE)) {
    return true;
  }
  return false;
}

bool is_ennemy_piece(pion grille[][WIDTH_TABLE], player current_player,
                     pos piece) {
  if (grille[piece.y][piece.x] == PION_EMPTY) {
    return false;
  }
  if ((current_player == PLAYER_BLACK) &&
      (grille[piece.y][piece.x] == PION_WHITE)) {
    return true;
  }
  if ((current_player == PLAYER_WHITE) &&
      (grille[piece.y][piece.x] == PION_BLACK)) {
    return true;
  }
  return false;
}
void do_move(pion grille[][WIDTH_TABLE], move move_played) {
  grille[move_played.destination.y][move_played.destination.x] =
      grille[move_played.piece.y][move_played.piece.x];
  grille[move_played.piece.y][move_played.piece.x] = PION_EMPTY;
  int relative_dist = move_played.piece.y - move_played.destination.y;
  if (relative_dist * relative_dist > 1) {
    pos ennemy;
    ennemy.y = (move_played.destination.y + move_played.piece.y) / 2;
    ennemy.x = (move_played.destination.x + move_played.piece.x) / 2;
    grille[ennemy.y][ennemy.x] = PION_EMPTY;
  }
}

void player_turn(pion grille[][WIDTH_TABLE], player current_player) {
  move possible_moves[40];
  int nb_moves = 0;
  get_possible_moves(grille, current_player, possible_moves, &nb_moves);
  move player_move;
  ask_joueur_move(grille, &player_move, possible_moves, nb_moves);
  do_move(grille, player_move);
}

void check_move_piece(pion grille[][WIDTH_TABLE], player current_player,
                      pos pion, pos dest, move possible_moves[], int* nbMoves) {
  if (grille[dest.y][dest.x] != PION_EMPTY) {
    return;
  }
  move temp;
  temp.destination = dest;
  temp.piece = pion;
  possible_moves[*nbMoves] = temp;
  *nbMoves += 1;
}

void check_moves_piece(pion grille[][WIDTH_TABLE], player current_player,
                       pos pion, move possible_moves[], int* nbMoves) {
  pos dest;
  int devant = +1;
  if (current_player == PLAYER_BLACK) {
    devant = -1;
  }
  if ((pion.y + devant > 0) && (pion.y + devant < HEIGHT_TABLE)) {
    if (pion.x + 1 < WIDTH_TABLE) {
      dest.x = pion.x + 1;
      dest.y = pion.y + devant;
      check_move_piece(grille, current_player, pion, dest, possible_moves,
                       nbMoves);
    }
    if (pion.x - 1 > 0) {
      dest.x = pion.x - 1;
      dest.y = pion.y + devant;
      check_move_piece(grille, current_player, pion, dest, possible_moves,
                       nbMoves);
    }
  }
}

void check_is_eating_move(pion grille[][WIDTH_TABLE], player current_player,
                          pos pion, pos possible_ennemy, move possible_moves[],
                          int* nbMoves, bool* can_eat) {
  pos dest;
  dest.y = 2 * possible_ennemy.y - pion.y;
  dest.x = 2 * possible_ennemy.x - pion.x;
  if ((dest.y < 0) || (dest.y >= HEIGHT_TABLE) || (dest.x < 0) ||
      (dest.x >= WIDTH_TABLE)) {
    return;
  }
  if ((is_ennemy_piece(grille, current_player, possible_ennemy)) &&
      (grille[dest.y][dest.x] == PION_EMPTY)) {
    if (*can_eat == false) {
      *can_eat = true;
      *nbMoves = 0;
    }
    move eat_move;
    eat_move.piece = pion;
    eat_move.destination = dest;
    possible_moves[*nbMoves] = eat_move;
    *nbMoves += 1;
    printf("je peux manger !\n");
  }
}
void check_eat_moves_piece(pion grille[][WIDTH_TABLE], player current_player,
                           pos pion, move possible_moves[], int* nbMoves,
                           bool* can_eat) {
  pos possible_ennemy;
  possible_ennemy.y = pion.y - 1;
  possible_ennemy.x = pion.x - 1;
  check_is_eating_move(grille, current_player, pion, possible_ennemy,
                       possible_moves, nbMoves, can_eat);
  possible_ennemy.x = pion.x + 1;
  check_is_eating_move(grille, current_player, pion, possible_ennemy,
                       possible_moves, nbMoves, can_eat);
  possible_ennemy.y = pion.y + 1;
  check_is_eating_move(grille, current_player, pion, possible_ennemy,
                       possible_moves, nbMoves, can_eat);
  possible_ennemy.x = pion.x - 1;
  check_is_eating_move(grille, current_player, pion, possible_ennemy,
                       possible_moves, nbMoves, can_eat);
}

void get_possible_moves(pion grille[][WIDTH_TABLE], player current_player,
                        move possible_moves[], int* nbMove) {
  pos piece;
  *nbMove = 0;
  bool can_eat = false;
  for (int y = 0; y < HEIGHT_TABLE; y++) {
    piece.y = y;
    for (int x = 0; x < WIDTH_TABLE; x++) {
      piece.x = x;
      if (is_his_piece(grille, current_player, piece)) {
        check_eat_moves_piece(grille, current_player, piece, possible_moves,
                              nbMove, &can_eat);
        if (!can_eat) {
          check_moves_piece(grille, current_player, piece, possible_moves,
                            nbMove);
        }
      }
    }
  }
}

int compte_piece_equipe(pion grille[][WIDTH_TABLE], player player_counted);
void one_turn(pion grille[][WIDTH_TABLE]);
void combo(pion grille[][WIDTH_TABLE], pos movedPion);
bool is_coup_valide(pion grille[][WIDTH_TABLE], pos piece, pos dest);
bool is_over(pion grille[][WIDTH_TABLE]);

void move_pion(pion grille[][WIDTH_TABLE], pos piece, pos dest) {
  grille[dest.y][dest.x] = grille[piece.y][piece.x];
  grille[piece.y][piece.x] = PION_EMPTY;
}
