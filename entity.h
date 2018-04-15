#ifndef ENTITY_H
#define ENTITY_H

#include "poulet.h"

void create(int type, float x, float y, struct Entity e[]);
void kill(struct Entity *e);
void readSpawns(int x, int y, struct Spawn s[], struct Entity e[]);
void recycle(struct Entity *e, struct Game *g);
void makeSpawn(int x, int y, int kind, struct Spawn s[]);

#endif
