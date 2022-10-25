#include "dames.h"

#include <stdio.h>

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
  for (int y = 0; y < HEIGHT_TABLE; y++) {
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

void ask_joueur(pion grille[][WIDTH_TABLE], pos piece, pos dest,
                player current_player) {
  selection_pion(grille, piece, current_player);
}

void selection_pion(pion grille[][WIDTH_TABLE], pos piece,
                    player current_player) {
  bool isValid = false;
  int x = 0;
  int y = 0;
  while (!isValid) {
    printf("Veuillez sélectionner les coordonnées du pion à bouger ! x y\n");
    scanf("%d %d", &x, &y);
    if ((x < 0) || (x >= WIDTH_TABLE) || (y < 0) || (y >= HEIGHT_TABLE)) {
      printf("Valeurs en dehors de la range !!!!\n");
    } else if (((grille[y][x] == PION_BLACK &&
                 current_player != PLAYER_BLACK)) ||
               ((grille[y][x] == PION_WHITE &&
                 current_player != PLAYER_WHITE))) {
      printf("Ceci n'est pas votre pion !\n");
    } else if (grille[y][x] == PION_EMPTY) {
      printf("Cet endroit est vide ! \n");
    } else {
      isValid = true;
      printf("valeur du pion %d", grille[y][x]);
    }
  }
}

void selection_move(pion grille[][WIDTH_TABLE], pos piece, pos dest,
                    player current_player) {
  bool isValid = false;
  int x = 0;
  int y = 0;
  while (!isValid) {
    printf("Veuillez sélectionner les coordonnées du pion à bouger ! x y\n");
    scanf("%d %d", &x, &y);
    if ((x < 0) || (x >= WIDTH_TABLE) || (y < 0) || (y >= HEIGHT_TABLE)) {
      printf("Valeurs en dehors de la range !!!!\n");
    } else if (((grille[y][x] == PION_BLACK &&
                 current_player != PLAYER_BLACK)) ||
               ((grille[y][x] == PION_WHITE &&
                 current_player != PLAYER_WHITE))) {
      printf("Ceci n'est pas votre pion !\n");
    } else if (grille[y][x] == PION_EMPTY) {
      printf("Cet endroit est vide ! \n");
    } else {
      isValid = true;
      printf("valeur du pion %d", grille[y][x]);
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

void player_turn(pion grille[][WIDTH_TABLE], player current_player) {}

void check_move_piece(pion grille[][WIDTH_TABLE], player current_player,
                      pos pion, pos dest, move possible_moves[], int* nbMoves) {
  if (grille[pion.y][pion.x] != PION_EMPTY) {
    return;
  }
  move temp;
  temp.destination = dest;
  temp.piece = pion;
  possible_moves[*nbMoves] = temp;
  nbMoves += 1;
}

void check_moves_piece(pion grille[][WIDTH_TABLE], player current_player,
                       pos pion, move possible_moves[], int* nbMoves) {
  pos dest;
  int devant = +1;
  if (current_player == PLAYER_WHITE) {
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

void check_eat(pion grille[][WIDTH_TABLE], player current_player, pos pion,
               move possible_moves[], int* nbMoves, bool* can_eat) {
  pos truc = machin;
}

void get_possible_moves(pion grille[][WIDTH_TABLE], player current_player,
                        move possible_moves[80], int* nbMove) {
  pos piece;
  *nbMove = 0;
  bool* can_eat = false;
  for (int y = 0; y < HEIGHT_TABLE; y++) {
    piece.y = y;
    for (int x = 0; x < WIDTH_TABLE; x++) {
      piece.x = x;
      if (is_his_piece(grille, current_player, piece)) {
        if (!can_eat) {
          check_moves_piece(grille, current_player, piece, possible_moves,
                            nbMove);
        }
        check_eat(grille, current_player, piece, possible_moves, nbMove,
                  can_eat);
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
