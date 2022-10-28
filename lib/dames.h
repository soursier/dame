#ifndef DAMES
#define DAMES

#include <stdbool.h>
#define WIDTH_TABLE 10
#define HEIGHT_TABLE 10

typedef struct Pos {
  int x;
  int y;
} pos;

typedef struct Move_ {
  pos piece;
  pos destination;
} move;

typedef enum Pion { PION_EMPTY = 0, PION_WHITE, PION_BLACK } pion;

typedef enum Player { PLAYER_WHITE = 0, PLAYER_BLACK } player;

void init_table(pion grille[][WIDTH_TABLE]);
void game();
void print_board(pion grille[][WIDTH_TABLE]);
void print_moves(pion grille[][WIDTH_TABLE], player current_player);
void print_combos(pion grille[][WIDTH_TABLE], player current_player);
void print_win();
void player_turn(pion grille[][WIDTH_TABLE], player current_player);
void ask_joueur(pion grille[][WIDTH_TABLE], pos piece, pos dest,
                player current_player);
void selection_pion(pion grille[][WIDTH_TABLE], pos* piece,
                    move possible_moves[], int nb_moves);
void selection_move(pion grille[][WIDTH_TABLE], pos piece, pos* dest,
                    move possible_moves[], int nb_moves);
int compte_piece_equipe(pion grille[][WIDTH_TABLE], player player_counted);
void one_turn(pion grille[][WIDTH_TABLE]);
void combo(pion grille[][WIDTH_TABLE], pos movedPion);
bool is_coup_valide(pion grille[][WIDTH_TABLE], pos piece, pos dest);
bool is_over(pion grille[][WIDTH_TABLE]);
void move_pion(pion grille[][WIDTH_TABLE], pos piece, pos dest);
void get_possible_moves(pion grille[][WIDTH_TABLE], player current_player,
                        move possible_moves[], int* nbMove);
#endif