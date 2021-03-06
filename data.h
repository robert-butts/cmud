#ifndef datah
#define datah

#include <stddef.h> /* needed for size_t */
#include <ncurses.h> /* needed for WINDOW */
#include <time.h> /* needed for time_t */
/* use to build with -Wextra with unused function params */
#define UNUSED(x) (void)(x)

typedef unsigned long id_t;
id_t next_id(); /* totally not threadsafe  */

/* this ought to be in gui.h, but that would be a circular dependency */
typedef struct {
  WINDOW* Main;
  WINDOW* Status;
} windows;

typedef struct {
  int X;
  int Y;
} point;
point point_create(int x, int y);
int point_equals(point* a, point* b); /* @returns 0 iff points are equal */

typedef struct {
  id_t Id;
  point Point;
  char Symbol; /* @todo make this work with multibyte unicode characters */
  short Color;
} map_object;
map_object map_object_create(int x, int y, char symbol, short color);
int map_object_equals(map_object* a, map_object* b); /* @returns 0 iff objects are equal */


typedef struct {
  map_object* Objects;
  size_t* Length;
  size_t* Size;
} map_list;
map_list map_create(size_t initialCapacity);
void map_destroy(map_list* list);
void map_reallocate(map_list* list); /* @todo determine if this needs to be exposed */
void map_add(map_list* map, int x, int y, char symbol, short color);
void map_add_object(map_list* map, map_object object);
void map_remove_object(map_list* map, map_object* object); /* removes the first object in the list which matches the given object */
map_list map_objects_in_box(map_list* list, int top, int left, int bottom, int right); /* @returns a new map_list of the objects within the given box. New map_list is new, not a modification of the old list */
map_object* map_get(map_list* list, point p);

/* @todo pack booleans */
typedef struct {
  map_object MapObject;
  const char* Name;
  const char* Desc;
  short MaxHealth;
  short Health;
  int Aggro;
  int Dead;
  time_t reviveTime;
} npc;

typedef struct {
  point Location;
  short Color;
  const char* Symbol;
  short MaxHealth;
  short Health;
  unsigned long Experience;
} player;

int player_level(player* p);

typedef struct {
  npc* Npcs;
  size_t* Length;
  size_t* Size;
  map_list* MapList;
} npc_list;
npc_list npc_list_create(size_t initialCapacity, map_list* mapList);
void npc_list_destroy(npc_list* list);

int npc_equals(npc* a, npc* b); /* @returns 0 iff npcs are equal */
npc npc_create(int x, int y, char symbol, short color, const char* name, const char* desc, short max_health);
/* @todo return npc created? */
void npc_add(npc_list* list, 
		 int x, 
		 int y, 
		 char symbol, 
		 short color, 
		 const char* name, 
		 const char* desc, 
		 short maxHealth,
		 int aggro);
void npc_reallocate(npc_list* list); /* @todo determine if this needs exposed */
void npc_add_object(npc_list* list, npc n);
void npc_remove(npc_list* list, npc* n); /* removes the first object in the list */
npc* npc_get(npc_list* list, id_t id); /* get an npc from the list by id */

typedef struct {
  map_list Map;
  npc_list Npcs;
  player Player;
  windows Windows;
  int WindowWidth;
  int WindowHeight;

  npc_list deadNpcs;
} world;

void world_refresh(world* w);

void tick(world* w);
void npc_tick(world* w, npc* n);
#endif
