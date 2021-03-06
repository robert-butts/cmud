#ifndef inputH
#define inputH

#include "data.h"

typedef enum {north, south, east, west} direction;

void handleInput(world* w, int* done); /* returns when done is true, or the user breaks */
void handleMouse(world* w);
void handleKey(int c, world* w);

void player_move(direction d, world* w);
void player_attack(world* w);
void npc_kill(world* w, npc* n);
void npc_revive(world* w, npc* n);

#endif
